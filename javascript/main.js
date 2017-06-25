window.onload = function() {
	var canvas = document.getElementById("canvas"),
		context = canvas.getContext("2d"),
		width = canvas.width = window.innerWidth / 2,
		height = canvas.height = window.innerHeight  / 2;

	for(var i = 0; i < 50; i += 1) {
		context.beginPath();
		context.moveTo(Math.random() * width, Math.random() * height);
		context.lineTo(Math.random() * width, Math.random() * height);
		context.stroke();
	}
};