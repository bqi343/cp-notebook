var sheet, DATA;
var numProblems, numWinners;
var probCol = 6, nameRow = 8;
var ui = SpreadsheetApp.getUi();
var name = "";
var totPoints = 0, numParticipants = 0, emailMode, yourEmail;

function genName() {
  name = SpreadsheetApp.getActiveSpreadsheet().getName();
  if (name.length >= 8 && name.substring(name.length-8,name.length).toLowerCase() == " results")
    name = name.substring(0,name.length-8);
}

function onOpen() {
  ui.createAddonMenu()
      .addItem('Initialize Sheet', 'init')
      .addItem('Generate Results', 'RESULTS')
      .addItem('Email Results', 'EMAIL')
      .addToUi();
  ui.alert('To grade, use the dynamic scoring add-on.');
}

function Comp(a, b) {
   if (a[0] != b[0]) return b[0]-a[0];
   return a[1]-b[1];
}

function getWeight(percent, type) {
  if (percent == 0) return 0;
  switch (type) {
    case 0:   
      return 1+Math.log(100/percent);
    case 1:
      if (percent <= 5.738) return 8;
      if (percent <= 13.208) return 7;
      if (percent <= 23.333) return 6;
      if (percent <= 37.838) return 5;
      if (percent <= 60.345) return 4;
      return 3;
    default:
      return 1;
  }
}

function input() {
  sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  DATA = sheet.getDataRange().getValues();
  genName();
  
  numProblems = parseInt(sheet.getRange(2,2).getValue());
  if (isNaN(numProblems)) {
    numProblems = 12;
    sheet.getRange(2,2).setValue(12);
  }
  
  win = parseInt(sheet.getRange(3,2).getValue());
  if (isNaN(win)) {
    win = 8;
    sheet.getRange(3,2).setValue(8);
  }
  
  emailMode = parseInt(sheet.getRange(4,2).getValue());
  if (isNaN(emailMode)) {
    emailMode = 0;
    sheet.getRange(4,2).setValue(0);
  }
  
  yourEmail = sheet.getRange(5,2).getValue();
  
  numParticipants = 0;
  for (var i = nameRow; i <= 100; ++i) if(sheet.getRange(i,1).getValue().length > 0) numParticipants ++; 
  sheet.getRange(1,2).setValue(numParticipants);
}

function init() {
  input();
  
  // correct # of rows + columns
  if (sheet.getMaxColumns() >= numProblems+probCol) sheet.deleteColumns(numProblems+probCol,sheet.getMaxColumns()-(numProblems+probCol)+1); 
  if (sheet.getMaxRows() >= 100) sheet.deleteRows(100,sheet.getMaxRows()-100+1); 
  
  // clear all colors  
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setFontStyle("normal");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setBackground("white");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setHorizontalAlignment("left");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setFontFamily("Times New Roman");
  
  // labels
  sheet.getRange(1,1).setValue("# of Participants");
  sheet.getRange(2,1).setValue("# of Problems");
  sheet.getRange(3,1).setValue("# of Winners");
  sheet.getRange(4,1).setValue("Email Mode");
  sheet.getRange(5,1).setValue("Your Email");
  
  for (var i = 1; i <= numProblems; ++i) sheet.getRange(nameRow-1,i+probCol-1).setValue(i);
  sheet.getRange(1,probCol-1,3,1).setValues([["Answer Key"],["%"],["Weight"]]);
  sheet.getRange(1,probCol-1,3,1).setFontStyle("italic");
  sheet.getRange(nameRow-1,1,1,probCol-1).setValues([["Name","Email","Email Sent","School","Score"]]);
  
  // freezing
  sheet.setFrozenColumns(probCol-1);
  sheet.setFrozenRows(nameRow-1);
  
  // columns
  for (var i = 1; i <= sheet.getMaxColumns(); ++i) {
      if (i >= probCol) sheet.setColumnWidth(i,60);
      else {
        sheet.autoResizeColumn(i);
        if (sheet.getColumnWidth(i) < 40) sheet.setColumnWidth(i,40);
      }
  }
}

function normalizeScore() {
  for (var i = nameRow-1; i < nameRow-1+numParticipants; i++)
    sheet.getRange(i+1,probCol-1).setValue(sheet.getRange(i+1,probCol-1).getValue()/totPoints*100); 
}

function RESULTS() {
  init();
  
  if (numParticipants == 0) {
    ui.alert('Please enter data!');
    return;
  } 
  
  DATA = sheet.getDataRange().getValues(), arr = [[]];
  for (var i = nameRow-1; i < nameRow-1+numParticipants; i++) sheet.getRange(i+1,probCol-1).setValue(0);
  for (var j = 0; j < numProblems; ++j) {
    var ans = 0;
    for (var i = nameRow-1; i < nameRow-1+numParticipants; i++) {
      if (DATA[i][j+probCol-1] == DATA[0][j+probCol-1]) {
        ans++; 
        sheet.getRange(i+1,j+probCol).setBackgroundRGB(0,255,0);
      } else {
        sheet.getRange(i+1,j+probCol).setBackgroundRGB(255,0,0);
      }
    }
    arr[0].push(100*ans/numParticipants);
  }
  sheet.getRange(2,probCol,1,numProblems).setValues(arr); 
  
  for (var i = 0; i < numProblems; ++i) arr[0][i] = getWeight(arr[0][i],0); // now generate weights

  for (var i = 0; i < numProblems; ++i) { 
    sheet.getRange(3,probCol+i).setValue(arr[0][i]); // set weights 
    totPoints += arr[0][i];
  }
  
  for (var j = 0; j < numProblems; ++j) {
    for (var i = nameRow-1; i < nameRow-1+numParticipants; i++) {
      if (DATA[i][j+probCol-1] == DATA[0][j+probCol-1]) {
        sheet.getRange(i+1,probCol-1).setValue(sheet.getRange(i+1,probCol-1).getValue()+arr[0][j]);
      } 
    }
  }
  
  normalizeScore();
  
  // sort participants by score
  var range = sheet.getRange(nameRow,1,numParticipants,numProblems+probCol-1);
  range.sort({column: probCol-1, ascending: false});
  for (var j = nameRow; j < nameRow+Math.min(win,numParticipants); ++j) sheet.getRange(j,1).setBackground("Yellow");
}

function EMAIL() {
  input();
  
  for (var i = nameRow-1; i < nameRow-1+DATA[0][1]; ++i) {
    var row = DATA[i], message = "Here is <b>"+row[0]+"'s</b> score report for the <b>" + name + "</b>.<br><br>";
    
    message += "Your final score is <b>"+Math.round(1000*row[probCol-2])/1000+"</b> out of 100.<br><br>";
    
    message += "<table style='width:100%;'border = 1 cellpadding = 5>"
      + "<tr>"
        + "<th>Question</th>"
        + "<th>Correct Answer</th>"
        + "<th>Percent</th>"
        + "<th>Weight</th>"
        + "<th>Your Answer</th>"
      + "</tr>";

   for (var j = probCol-1; j < probCol-1+numProblems; ++j) {
      message += "<tr>"
                  +"<td>"+(j-probCol+2)+"</td>"
                  +"<td>"+DATA[0][j]+"</td>"
                  +"<td>"+Math.round(1000*DATA[1][j])/1000+"%</td>"
                  +"<td>"+Math.round(1000*DATA[2][j])/1000+"</td>"
                  +"<td>";
      message += row[j];
      message += "</td></tr>";
    }
    message += "</table><br><br>"
    + "Please respond if you have any questions."
    + "<br><br><i>Generated by the <a href=\"https://github.com/bqi343/USACO/blob/master/Other/Dynamic%20Scoring.gs\">Dynamic Scoring</a> "
    + "addon.</i>";

    if (row[2] != "Yes" && emailMode == 1) {
      MailApp.sendEmail({to: row[1],subject: name+" Score Report",htmlBody: message});
      sheet.getRange(i+1,3).setValue("Yes");
    }
    
    if (i == nameRow-1 && emailMode == 0) 
      MailApp.sendEmail({to: yourEmail,subject: name+" Score Report",htmlBody: message});
  }
}
