const net = require('net');
const fs = require('fs');

var domainSocketPath;
var clientExec = false;

fs.readFile(clientExec ? 'src/api/utils/domainSockets/sharedConfig.txt' : '../sharedConfig.txt', function read(error, data) {
	if (error) { throw error; }
	domainSocketPath = data;

	createServer();
});

function createServer() {
	fs.unlink("/tmp/spotifyclientsock.sock", function() {
		var server = net.createServer(function(socket) {
			console.log("Connection");

			socket.on('data', function(data) {
				console.log(`Received data ${data}\n`);
				parseCommand(data);
			});

			socket.on('error', function(error) {
				console.log(`Error: ${error}`);
			});
		});
		server.listen("/tmp/spotifyclientsock.sock", function() {
			console.log("Created server");
		})
	})
}

function parseCommand(command) {
	switch (command) {
		case 'play':
			sendPlayRequest();
			break;
		case 'pause':
			sendPauseRequest();
			break;
		case 'previous':
			sendPreviousSongRequest();
			break;
		case 'skip':
			sendSkipSongRequest();
			break;
		case 'toggleShuffle':
			sendToggleShuffleRequest();
			break;
		case 'toggleLoop':
			sendToggleLoopRequest();
			break;
	}
}

function sendPlayRequest() {

}

function sendPauseRequest() {

}

function sendPreviousSongRequest() {

}

function sendSkipSongRequest() {

}

function sendToggleShuffleRequest() {

}

function sendToggleLoopRequest() {

}
