/*
User:

Provide an example of how to configure NodeJS on a web server to serve an HTML file.

ChatGPT:

Configuring Node.js on a web server to serve an HTML file is relatively simple. First, you'll need to have Node.js installed on your system. You can download it from the official Node.js website.

Once Node.js is installed, follow these steps:

    Create a New Directory: Create a new directory where your project will reside.

    sh

mkdir my-node-server
cd my-node-server

Initialize a New Node.js Project: Run npm init to create a new Node.js project. This command will create a package.json file.

sh

npm init -y

Install Express: Express is a popular web application framework for Node.js. Install it using npm (Node package manager).

sh

npm install express

Create an HTML File: Create a new file named index.html in your project directory, and add some HTML content to it.

html
* / 
<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>My Node.js Server</title>
</head>
<body>
    <h1>Hello, World!</h1>
</body>
</html>

Create the Server: Create a new JavaScript file named server.js. This file will create an HTTP server that serves your HTML file.

javascript
*/
// server.js
const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

// Serve static files from the root directory
app.use(express.static(path.join(__dirname)));

// Route to serve the HTML file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

// Start the server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
/*
Start the Server: Finally, run your server using Node.js:

sh

    node server.js

    Access the Server: Open your web browser and go to http://localhost:3000. You should see the content of your HTML file being served.

Please note that this example is intended for local development and learning purposes. If you're planning to deploy a Node.js application to a production environment, you should consider using a more robust configuration, which includes proper security measures, performance optimizations, and using a reverse proxy like Nginx.
*/

const http = require('http');
const fs = require('fs');
const path = require('path');

const server = http.createServer((req, res) => {
    let filePath = path.join(__dirname, 'public', req.url);
    let contentType = 'text/html';
    const extname = path.extname(filePath);

    switch (extname) {
        case '.css':
            contentType = 'text/css';
            break;
        case '.js':
            contentType = 'application/javascript';
            break;
        default:
            contentType = 'text/html';
    }

    fs.readFile(filePath, (err, content) => {
        if (err) {
            res.writeHead(500);
            res.end(`Server Error: ${err.code}`);
        } else {
           // res.setHeader("Content-Security-Policy", "script-src 'self'; style-src 'self'");
            res.writeHead(200, { 'Content-Type': contentType });
            
            res.end(content, 'utf-8');
        }
    });
});
server.listen();

//

var http = require('http');
var server = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    var message = 'It works!\n',
        version = 'NodeJS ' + process.versions.node + '\n',
        response = [message, version].join('\n');
    res.end(response);
});
server.listen();

//

var express = require('express');
var path = require('path');
var app = express();

// Serve static files from the root directory
app.use(express.static(path.join(__dirname)));

// Route to serve the HTML file
app.get(__dirname, (req, res) => {
    res.sendFile(path.join(__dirname, 'public','index.html'));
});

// Start the server
app.listen();

