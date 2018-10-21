var sheet, DATA;
var numProblems, numWinners;
var nameRow, probCol;
var ui = SpreadsheetApp.getUi();
var name = "";
var totPoints = 0, numParticipants = 0, emailMode, yourEmail, weightSystem;

function moveFiles(sourceFileId, targetFolderId) {
  var file = DriveApp.getFileById(sourceFileId);
  file.getParents().next().removeFile(file);
  DriveApp.getFolderById(targetFolderId).addFile(file);
}

function getFolder() {
  var thisFileId = SpreadsheetApp.getActiveSpreadsheet().getId();
  var thisFile = DriveApp.getFileById(thisFileId);
  return thisFile.getParents().next();
}

function checkFile(folder,filename){
  var file = folder.getFilesByName(filename);
  return file.hasNext();
}

function genForm() {
  genName();
  var contents = getFolder().getFiles();
  var existsForm = false;
  while (contents.hasNext()) {
    var file = contents.next();
    var name = file.getName();
    if (name.length >= 6 && name.substring(name.length-6,name.length) == "Signup") existsForm = true;
  }
  
  return;
  if (!existsForm) {
    var title = name+" Signup";
    var form = FormApp.create(title);
    moveFiles(form.getId(),getFolder().getId());
  }
  
  form.addTextItem()
  .setTitle("Name")
  .setRequired(true);
  
  var v = form.addTextItem()
  .setTitle("Email Address")
  .setRequired(true);
  v.setValidation(FormApp.createTextValidation().setHelpText("Enter valid email.").requireTextIsEmail().build());
  
  form.addMultipleChoiceItem()
  .setTitle('I can take the tryout test on the following date.')
  .setChoiceValues(['?','?'])
  .setRequired(true)
  .showOtherOption(true);
  
  form.addMultipleChoiceItem()
  .setTitle('I am able to attend the contest on ----.')
  .setChoiceValues(['Yes','No'])
  .setRequired(true);
  
  form.addParagraphTextItem()
  .setTitle('Any comments?');
  
  form.setDestination(FormApp.DestinationType.SPREADSHEET,SpreadsheetApp.getActiveSpreadsheet().getId());
}

function genName() {
  name = SpreadsheetApp.getActiveSpreadsheet().getName();
  if (name.length >= 8 && name.substring(name.length-8,name.length).toLowerCase() == " results")
    name = name.substring(0,name.length-8);
}

function onOpen() {
  ui.createAddonMenu()
      .addItem('Initialize Spreadsheet', 'init')
      .addItem('Generate Results', 'RESULTS')
      .addItem('Email Results', 'EMAIL')
      .addToUi();
  ui.alert('To grade, use the dynamic scoring add-on.');
}

function Comp(a, b) {
   if (a[0] != b[0]) return b[0]-a[0];
   return a[1]-b[1];
}

function getWeight(prob, percent) {
  switch(weightSystem) {
    case "PUMaC":
      if (percent == 0) return 0;
      return 1+Math.log(100/percent);
    case "ARML":
      return 1;
    case "Original":
      return 12075/32/(percent+175/4)-1/8; // https://docs.google.com/document/d/1Q1Rf3dI6QpXweCkAm4Yt1DOB9yKUOIW7bvxfqSEfUM8/edit
    default:
      return DATA[2][probCol-1+prob];
  }
}

function input() {
  sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  DATA = sheet.getDataRange().getValues();
  genName();
  
  numProblems = parseInt(sheet.getRange(3,2).getValue());
  if (isNaN(numProblems)) {
    numProblems = 12;
    sheet.getRange(3,2).setValue(12);
  }
  
  win = parseInt(sheet.getRange(4,2).getValue());
  if (isNaN(win)) {
    win = 8;
    sheet.getRange(4,2).setValue(8);
  }
  
  emailMode = 0;
  if (sheet.getRange(6,2).getValue() == "Active") emailMode = 1;
  else emailMode = 0;
  
  yourEmail = sheet.getRange(7,2).getValue();
}

function format() {
  // correct # of rows + columns
  if (sheet.getMaxColumns() >= numProblems+probCol) sheet.deleteColumns(numProblems+probCol,sheet.getMaxColumns()-(numProblems+probCol)+1); 
  if (sheet.getMaxRows() >= 100) sheet.deleteRows(100,sheet.getMaxRows()-100+1); 
  
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setFontStyle("normal");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setHorizontalAlignment("left");
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setFontFamily("Times New Roman");
  
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

var info = ["# of Participants","# of Problems","# of Winners","Scoring System","Email Mode","Your Email"];
var col = ["Name","Email","Email Sent","School","Score"];

function label() {
  sheet.getRange(1,1).setFontWeight("bold");
  sheet.getRange(1,1).setValue("Basic Information"); 
  for (var i = 0; i < info.length; ++i) sheet.getRange(i+2,1).setValue(info[i]); 
  sheet.getRange(5,2).setDataValidation(SpreadsheetApp.newDataValidation().requireValueInList(['Given', 'ARML', 'PUMaC','Original'], true).build());
  sheet.getRange(6,2).setDataValidation(SpreadsheetApp.newDataValidation().requireValueInList(['Inactive', 'Active'], true).build());
  if (sheet.getRange(7,2).getValue().length == 0) sheet.getRange(7,2).setValue("[Email]");
  
  nameRow = info.length+4;
  probCol = col.length+1;
  
  for (var i = 1; i <= numProblems; ++i) sheet.getRange(nameRow-1,i+probCol-1).setValue(i);
  sheet.getRange(1,probCol-1,3,1).setValues([["Answer Key"],["%"],["Weight"]]);
  sheet.getRange(1,probCol-1,3,1).setFontStyle("italic");
  sheet.getRange(nameRow-1,1,1,probCol-1).setValues([col]);
}

var contacts;

function tri(x) {
  x = x.toLowerCase();
  if (x in contacts) return contacts[x];
  return "";
}

function init() {
  input();
  genForm();
  label();
  format();
  
  var res = ContactsApp.getContacts();

  contacts = {};
  for (var i = 0; i < res.length; ++i) {
    var v = res[i].getEmails();
    for (var j = 0; j < v.length; ++j) {
      contacts[res[i].getFullName().toLowerCase()] = v[j].getAddress().toLowerCase();
    }
  }
  
  numParticipants = 0;
  for (var i = nameRow; i <= 100; ++i) 
    if (sheet.getRange(i,1).getValue().length > 0) {
      numParticipants ++; 
      if (sheet.getRange(i,2).getValue().length == 0) 
        sheet.getRange(i,2).setValue(tri(sheet.getRange(i,1).getValue()));
    }
  
  sheet.getRange(2,2).setValue(numParticipants);
}

function normalizeScore() {
  for (var i = nameRow-1; i < nameRow-1+numParticipants; i++)
    sheet.getRange(i+1,probCol-1).setValue(sheet.getRange(i+1,probCol-1).getValue()/totPoints*100); 
}

function genRGB(a) {
  return Math.round(2*a*255/100);
}

function RESULTS() {
  init();
  sheet.getRange(1,1,sheet.getMaxRows(),sheet.getMaxColumns()).setBackground("white");
  
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
  for (var i = 0; i < numProblems; ++i) {
    var v = genRGB(arr[0][i]);
    if (v >= 255) sheet.getRange(2,probCol+i).setBackgroundRGB(2*255-v,255,2*255-v);
    else sheet.getRange(2,probCol+i).setBackgroundRGB(255,v,v);
  }
  
  weightSystem = DATA[4][1];
  for (var i = 0; i < numProblems; ++i) { 
    arr[0][i] = getWeight(i,arr[0][i]); // generate weights
    sheet.getRange(3,probCol+i).setValue(arr[0][i]); // set weights 
    totPoints += arr[0][i];
  }
  
  var tot = [];
  for (var i = 0; i < numParticipants; ++i) tot.push(0);
  
  for (var j = 0; j < numProblems; ++j) {
    for (var i = nameRow-1; i < nameRow-1+numParticipants; i++) {
      if (DATA[i][j+probCol-1] == DATA[0][j+probCol-1]) {
        tot[i-(nameRow-1)] += arr[0][j];
      } 
    }
  }
  
  for (var i = nameRow-1; i < nameRow-1+numParticipants; i++) 
    sheet.getRange(i+1,probCol-1).setValue(tot[i-(nameRow-1)]);
  
  // sort participants by score
  var range = sheet.getRange(nameRow,1,numParticipants,numProblems+probCol-1);
  range.sort({column: probCol-1, ascending: false});
  for (var j = nameRow; j < nameRow+Math.min(win,numParticipants); ++j) sheet.getRange(j,1).setBackground("Yellow");
}

function EMAIL() {
  init();
  
  if (emailMode == 1) {
     var response = ui.alert('Are you sure that you want to email results to all participants?', ui.ButtonSet.YES_NO);
     if (response != ui.Button.YES) return;
  } else {
     var response = ui.alert('Are you sure that you want to email results to yourself?', ui.ButtonSet.YES_NO);
     if (response != ui.Button.YES) return;
  }
  
  for (var i = nameRow-1; i < nameRow-1+numParticipants; ++i) {
    var row = DATA[i], message = "Here is <b>"+row[0]+"'s</b> score report for the <b>" + name + "</b>.<br><br>";
    
    message += "Your final score is <b>"+Math.round(1000*row[probCol-2])/1000+"</b>. ";
    if (row[probCol-2] == 0) {
      message += "Better luck next time!";
    }
    message += "<br><br>";
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
    + "Please respond if you have any questions.";

    if (row[2] != "Yes" && emailMode == 1) {
      MailApp.sendEmail({to: row[1],subject: name+" Score Report",htmlBody: message});
      sheet.getRange(i+1,3).setValue("Yes");
    }
    
    if (i == nameRow-1 && emailMode == 0) 
      MailApp.sendEmail({to: yourEmail,subject: name+" Score Report",htmlBody: message});
  }
}
