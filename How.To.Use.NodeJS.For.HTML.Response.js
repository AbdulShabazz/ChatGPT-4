/*
Uaer:

How do I use nodeJS to write an html response?

ChatGPT:

Using Node.js, you can write an HTML response without using any additional frameworks like Express. The built-in http module in Node.js allows you to create a web server that can respond with HTML content. Here’s a simple example to get you started:

    Create a new directory for your project and navigate into it.

    sh

mkdir my-simple-node-server
cd my-simple-node-server

Create a JavaScript file named server.js to write your server code.

Add the following code to the server.js file.

javascript
*/
const http = require('http');

const server = http.createServer((req, res) => {
    // Set the content type to HTML
    res.writeHead(200, {'Content-Type': 'text/html'});

    // Write the HTML content
    res.write('<!DOCTYPE html>');
    res.write('<html>');
    res.write('<head><title>My Node.js Server</title></head>');
    res.write('<body>');
    res.write('<h1>Hello, World!</h1>');
    res.write('</body>');
    res.write('</html>');

    // End the response
    res.end();
});

const port = 3000;
server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

/*
This code creates an HTTP server using the built-in http module in Node.js. When a request is received, it sends an HTML response back to the client.

Run the server by executing the server.js file with Node.js.

sh

    node server.js

    Access the Server: Open your web browser and go to http://localhost:3000. You should see the HTML content you created being served.

This is a simple example to show you how to write HTML responses directly from Node.js. In real-world applications, 
you'd typically have more sophisticated routing and might serve HTML files instead of embedding the HTML in your server code. 
Using a web framework like Express would simplify many aspects of building a web application.
*/
