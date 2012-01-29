using UnityEngine;
using System.Collections;

public class TextureAnimation : MonoBehaviour {

public Texture[] framesWalkingRight;
public Texture[] framesWalkingLeft;
public Texture[] framesStartJumpingRight;
public Texture[] framesUpJumpingRight;
public Texture[] framesDownJumpingRight;
public Texture[] framesLandRight;
public Texture[] framesStartJumpingLeft;
public Texture[] framesUpJumpingLeft;
public Texture[] framesDownJumpingLeft;
public Texture[] framesLandLeft;
public Texture[] framesPushingRight;
public Texture[] framesPushingLeft;
public int framesPerSecond = 10;

void Update() 
{
	CharacterController CharController = transform.parent.GetComponent<CharacterController>();
	int index;
	if (Input.GetAxis("Horizontal") > 0 && CharController.isGrounded)
	{
		index = (int) (Time.time * framesPerSecond) % framesWalkingRight.Length;
		renderer.material.mainTexture =  framesWalkingRight[index];
	}
	else if(Input.GetAxis("Horizontal") < 0 && CharController.isGrounded)
	{
		index = (int)(Time.time * framesPerSecond) % framesWalkingLeft.Length;
		renderer.material.mainTexture =  framesWalkingLeft[index];
	}
	else if(!CharController.isGrounded)
	{
		index = (int)(Time.time * framesPerSecond) % framesUpJumpingRight.Length;
		renderer.material.mainTexture =  framesUpJumpingRight[index];
	}
}

void JumpAnimation(int state)
{
	int index;
	switch(state)
	{
		case 0:
			print("Start");
			index = (int)(Time.time * framesPerSecond) % framesStartJumpingRight.Length;
			renderer.material.mainTexture =  framesStartJumpingRight[index];
			break;
		case 1:
			print("Up");
			index = (int)(Time.time * framesPerSecond) % framesUpJumpingRight.Length;
			renderer.material.mainTexture =  framesUpJumpingRight[index];
			break;
		case 2:
			print("Down");
			index = (int)(Time.time * framesPerSecond) % framesDownJumpingRight.Length;
			renderer.material.mainTexture =  framesDownJumpingRight[index];
			break;
		case 3:
			print("Land");
			index = (int)(Time.time * framesPerSecond) % framesLandRight.Length;
			renderer.material.mainTexture =  framesLandRight[index];
			break;
	}
}
}
