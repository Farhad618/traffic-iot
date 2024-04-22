const express = require('express')
const app = express()
const port = 3001
var fs = require('fs');
const filename = "trafficstatus"

/**
 * 1 = stop
 * 2 = wait
 * 3 = go
 **/

app.get('/read-traffic', (req, res) => {
  fs.readFile(filename, function(err, data) {
    if (err) throw err;
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    console.log('Data fetched. ' + data)
    return res.end();
  });
})

app.get('/write-traffic', (req, res) => {
  console.log(req.query.t)
  fs.writeFile(filename, req.query.t, function (err) {
    if (err) throw err;
    console.log('Replaced!');
  });
  res.send(req.query.t)
})


app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})