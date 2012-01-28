var framesWalkingRight : Texture[];
var framesWalkingLeft  : Texture[];
var framesJumpingRight : Texture[];
var framesJumpingLeft  : Texture[];
var framesPushingRight : Texture[];
var framesPushingLeft  : Texture[];
var framesPerSecond = 10;

function Update() 
{
	var index:int;
	if (Input.GetAxis("Horizontal") > 0)
	{
		index = (Time.time * framesPerSecond) % framesWalkingRight.Length;
		renderer.material.mainTexture = framesWalkingRight[index];
	}
	else if(Input.GetAxis("Horizontal") < 0)
	{
		index = (Time.time * framesPerSecond) % framesWalkingLeft.Length;
		renderer.material.mainTexture = framesWalkingLeft[index];
	}
}