const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {

    user: 'agray15test@gmail.com',
    pass: 'bloobird90!'

	// naturally, replace both with your real credentials or an application-specific password
  }
});


var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;

app.get("/", function (req, res) {
    res.redirect("index.html")
});

app.get("/sendEmail", function (req, res) {
   // Send Email
   console.log("button pressed");
   transporter.sendMail(mailOptions, function(error, info){
     if (error) {
   	console.log(error);
     } else {
       console.log('Email sent: ' + info.response);
     }
   });
   res.send("1");
});

app.get("/sendData", function (req, res) {
   // Send data
   //t and h values
   var t = request.query.t;
   var h = request.query.h;
   
   const mailOptions = {
  from: 'agray15test@gmail',
  to: 'agray15@asu.edu',
  subject: 'test',
  //text: 'temperature' + "t" 'humidity' + "h"
  text: ' temperature + "t" humidity + "h" '
};
   console.log("button pressed");
   transporter.sendMail(mailOptions, function(error, info){
     if (error) {
   	console.log(error);
     } else {
       console.log('Email sent: ' + info.response);
     }
   });
   res.send("1");
});







app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
