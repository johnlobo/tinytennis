window.onload = function ()
{
    var canvas = document.getElementById("canvas"),
    context = canvas.getContext("2d"),
    width = canvas.width = window.innerWidth /2,
    height = canvas.height = window.innerHeight/2;
    context.fillStyle='lightblue';
	context.fillRect(0,0,canvas.width,canvas.height);

    function Ball(x, y, z, radius, context)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.px = x;
        this.py = y;
        this.pz = z;
        this.radius = radius;
        this.context = context;
        this.inc_z = 1;

        this.move = function (x, y, z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        this.print = function ()
        {
            //erase shadow
            this.context.clearRect(this.px-radius-4, this.py-radius-2+2, (this.radius*2)+(this.pz/4)+4, (this.radius)+(this.pz/4)+2)
            //erase ball
            this.context.clearRect(this.px-radius, this.py-this.pz-radius, this.radius*2, this.radius*2);

            //Shadow
            this.drawShadow(this.x, this.y+4, (this.radius*2)+(this.z/4), (this.radius)+(this.z/4)-4)
            //Ball
            this.context.beginPath();
            this.context.arc(this.x, this.y - this.z, this.radius, 0, 2 * Math.PI, false);
            this.context.fillStyle = 'yellow';
            this.context.fill();
            //this.context.closePath();

        };

        this.drawShadow = function (centerX, centerY, width, height)
        {

            this.context.beginPath();
            this.context.moveTo(centerX, centerY - height / 2); // A1

            this.context.bezierCurveTo(
                centerX + width / 2, centerY - height / 2, // C1
                centerX + width / 2, centerY + height / 2, // C2
                centerX, centerY + height / 2); // A2

            this.context.bezierCurveTo(
                centerX - width / 2, centerY + height / 2, // C3
                centerX - width / 2, centerY - height / 2, // C4
                centerX, centerY - height / 2); // A1

            this.context.fillStyle = "black";
            this.context.fill();
            //this.context.closePath();
        };
        this.update = function ()
        {
            if (this.z > 40)
            {
                this.inc_z = -1;
            }
            else if (this.z < 0)
            {
                this.inc_z = 1;
            }

            this.pz = this.z;
            this.z += this.inc_z;

        }

    }
    function gameLoop()
    {
        window.requestAnimationFrame(gameLoop);
        bola.update();
        bola.print();
    }

    var bola = new Ball(100, 100, 0, 4, context);
    gameLoop();
}
