const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    user: 'agray15test@gmail.com',
    pass: 'bloobird90!' // naturally, replace both with your real credentials or an application-specific password
  }
});

const mailOptions = {
  from: 'agray15test@gmail.com',
  to: 'agray15@asu.edu',
  subject: 'test',
  text: 'testing.'
};

transporter.sendMail(mailOptions, function(error, info){
  if (error) {
	console.log(error);
  } else {
    console.log('Email sent: ' + info.response);
  }
});

