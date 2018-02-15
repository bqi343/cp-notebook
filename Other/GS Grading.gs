var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Princeton"); // name of results sheet
var DATA;
var nP = 12, nC = 6, win = 7;
var tot = 0;
var ui = SpreadsheetApp.getUi();
var name = "";

function onOpen() {
  ui.createAddonMenu()
      .addItem('Generate Results', 'RESULTS')
      .addItem('Email Results', 'EMAIL')
      .addToUi();
  ui.alert('To grade, use the dynamic scoring add-on.');
}

function Comp(a, b) {
   if (a[0] != b[0]) return b[0]-a[0];
   return a[1]-b[1];
}

function getWeight(percent) {
  if (percent == 0) return 0;
  return 1+Math.log(100/percent);
  /*
  if (percent <= 5.738) return 8;
  if (percent <= 13.208) return 7;
  if (percent <= 23.333) return 6;
  if (percent <= 37.838) return 5;
  if (percent <= 60.345) return 4;
  return 3;*/
}

function init() {
  if (sheet.getMaxColumns() >= nP+nC) sheet.deleteColumns(nP+nC,sheet.getMaxColumns()-nP-nC+1); // correct # of columns
  
  // labels
  for (var i = 1; i <= nP; ++i) sheet.getRange(5,i+nC-1).setValue(i);
  sheet.getRange(1,nC-1,3,1).setValues([["Answer Key"],["%"],["Weight"]]);
  sheet.getRange(1,nC-1,3,1).setFontStyle("italic");
  sheet.getRange(5,1,1,nC-1).setValues([["Name","Email","Email Sent","School","Score"]]);
  
  // freezing
  sheet.setFrozenColumns(nC-1);
  sheet.setFrozenRows(5);
  
  // clear all colors  
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setBackground("white");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setHorizontalAlignment("left");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setFontFamily("Times New Roman");
  
  // columns
  for (var i = 1; i <= sheet.getMaxColumns(); ++i) sheet.autoResizeColumn(i);
}

function RESULTS() {
  init();
  var numParticipants = 0;
  for (var i = 6; i <= 100; ++i) if(sheet.getRange(i,1).getValue().length>0) numParticipants++; 
  sheet.getRange(1,1).setValue("Number of Participants");
  sheet.getRange(1,2).setValue(numParticipants);
  
  DATA = sheet.getDataRange().getValues(), arr = [[]];
  for (var i = 5; i < 5+numParticipants; i++) sheet.getRange(i+1,nC-1).setValue(0);
  for (var j = 0; j < nP; ++j) {
    var ans = 0;
    for (var i = 5; i < 5+numParticipants; i++) {
      if (DATA[i][j+nC-1] == DATA[0][j+nC-1]) {
        ans++; 
        sheet.getRange(i+1,j+nC).setBackgroundRGB(0,255,0);
      } else {
        sheet.getRange(i+1,j+nC).setBackgroundRGB(255,0,0);
      }
    }
    arr[0].push(100*ans/numParticipants);
  }
  sheet.getRange(2,nC,1,nP).setValues(arr); 
  
  for (var i = 0; i < nP; ++i) arr[0][i] = getWeight(arr[0][i]); // now generate weights

  tot = 0;
  for (var i = 0; i < nP; ++i) { 
    sheet.getRange(3,nC+i).setValue(arr[0][i]); // set weights 
    tot += arr[0][i];
  }
  
  for (var j = 0; j < nP; ++j) {
    for (var i = 5; i < 5+numParticipants; i++) {
      if (DATA[i][j+nC-1] == DATA[0][j+nC-1]) {
        sheet.getRange(i+1,nC-1).setValue(sheet.getRange(i+1,nC-1).getValue()+arr[0][j]);
      } 
    }
  }
  
    for (var i = 5; i < 5+numParticipants; i++)
      sheet.getRange(i+1,nC-1).setValue(sheet.getRange(i+1,nC-1).getValue()/tot*100);
  
  // sort participants by score
  var range = sheet.getRange(6,1,numParticipants,nP+nC-1);
  range.sort({column: nC-1, ascending: false});
  for (var j = 6; j < 6+Math.min(win,numParticipants); ++j) sheet.getRange(j,1).setBackground("Yellow");
}

function EMAIL() {
  DATA = sheet.getDataRange().getValues();
  
  for (var i = 5; i < 5+DATA[0][1]; ++i) {
    var row = DATA[i], message = "Here is <b>"+row[0]+"'s</b> score report for the <b>" + name + "</b>.<br><br>";
    
    message += "Your final score is <b>"+Math.round(1000*row[nC-2])/1000+"</b>.<br><br>";
    
    message += "<table style='width:100%;'border = 1 cellpadding = 5>"
      + "<tr>"
        + "<th>Question</th>"
        + "<th>Correct Answer</th>"
        + "<th>Percent</th>"
        + "<th>Weight</th>"
        + "<th>Your Answer</th>"
      + "</tr>";

   for (var j = nC-1; j < nC-1+nP; ++j) {
      message += "<tr>"
                  +"<td>"+(j-nC+2)+"</td>"
                  +"<td>"+DATA[0][j]+"</td>"
                  +"<td>"+Math.round(1000*DATA[1][j])/1000+"%</td>"
                  +"<td>"+Math.round(1000*DATA[2][j])/1000+"</td>"
                  +"<td>";
      if (row[j] != "X") message += row[j];
      message += "</td></tr>";
    }
    message += "</table><br><br>"
    + "Please respond if you have any questions.<br><br>~Ben";

    sheet.getRange(i+1,3).setValue("Yes");
    // if (row[2] != "Yes") MailApp.sendEmail({to: row[1],subject: name+" Score Report",htmlBody: message});
    if (i == 5) MailApp.sendEmail({to: "bqi343@gmail.com",subject: name+" Score Report",htmlBody: message});
  }
}
