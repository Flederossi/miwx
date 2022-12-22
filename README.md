# miwx
A micro web server for static content

## Usage
```
sudo miwx [port]
```

## Installation
### Linux:
> 1 - Compile and install miwx by using:
> ```
> make install
> ```
> Now miwx should be installed. To check, go to the templates folder and run:
> ```
> sudo miwx 80
> ```
> This will start the web server on port 80. If you now search for 'localhost' or '127.0.0.1' in your browser you should get the output:
> ```
> 127.0.0.1:29573 -> 127.0.0.1:80 | ./index.html
> 127.0.0.1:29574 -> 127.0.0.1:80 | ./style.css
> ```
> Also the example website should show up like this:
> Now you can run miwx in every folder of your machine to make that the root folder of the web server.
