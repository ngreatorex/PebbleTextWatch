Pebble.addEventListener("ready",
  function(e) {
    console.log("Text watchface ready and running!");
  }
);

Pebble.addEventListener("appmessage",
  function(e) {
    console.log("Received message: " + e.payload);
  }
);

