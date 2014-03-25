/* vim:set noet ts=2 sw=2: */

var settings = {
	"server": "http://raspi-d.lan:3000/",
	"selector": "tag%3aPebble%20Controlled",
};

Pebble.addEventListener("ready",
	function(e) {
		console.log("Text watchface ready and running!");
	}
);

Pebble.addEventListener("appmessage",
	function(e) {
		console.log("Received message with operation " + e.payload.operation);
		switch (e.payload.operation) {
			case "toggle":
				var req = new XMLHttpRequest();
				req.open('PUT', settings.server + 'lights/' + settings.selector + '/toggle', true);
				req.onload = function(e) {
					if (req.readyState == 4 && req.status == 200) {
						if(req.status == 200) {
							var response = JSON.parse(req.responseText);
							if (response) {
								console.log("Successfully toggled " + response.length + " lights");
							} else {
								console.log("Unable to toggle lights");
							}
						} else {
							console.log("Error");
						}
					}
				};
				console.log("Sending toggle request to " + settings.server);
				req.send(null);
		}
	}
);

