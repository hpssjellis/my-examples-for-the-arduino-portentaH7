

const http = require("http");

const hostname = "0.0.0.0";
const port = 8080;
var oldChunk = "";

const server = http.createServer((req, res) => {
  console.log(`\n${req.method} ${req.url}`);
  console.log(req.headers);

  req.on("data", function(chunk) {
    console.log("BODY: " + chunk);
    //OldChunk += "<textarea id='myArea01' rows=20 cols=70>";
   // oldChunk = JSON.stringify(chunk.toString('ascii'));
    oldChunk = chunk.toString('ascii');
    //oldChunk += "</textarea>";
  });
  
  res.statusCode = 200;
  res.setHeader("Content-Type", "text/plain");
  res.end(oldChunk);
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
