using UnityEngine;
using System.Collections;

public class Movement : MonoBehaviour {
	
	public Layer1 layer1;
	public Layer1 layer2;
	//public ArrayList cubes;
	//ArrayList.
	

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
		//tratando teclas de input
		if (Input.GetKey("d"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.right * 50);
			
			//other.Layer1ToFront(1);
			//gameObject.SendMessage("Layer1ToFront",1,SendMessageOptions.RequireReceiver);
			//BroadcastMessage("Layer1ToFront",1,SendMessageOptions.RequireReceiver);
			
		}
				if (Input.GetKeyUp("d"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.right * -0);
			
		}
		
		if (Input.GetKey("a"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.left * 50);
			
		}
				if (Input.GetKeyUp("a"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.left * -0);
			
		}
		
				if (Input.GetKey("w"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.up * 50);
			
		}
				if (Input.GetKeyUp("w"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.up * -0);
			
		}
		
				if (Input.GetKey("s"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.down * 50);
			
		}
				if (Input.GetKeyUp("s"))
		{
			//gameObject.transform.Translate(1,0,0);
			gameObject.constantForce.relativeForce = (Vector3.down * -0);
			
		}
		
		//movendo layers com t e g
		
			if (Input.GetKeyDown("t"))
		{
			layer1.Layer1ToFront(1);
		}
		
		if (Input.GetKeyDown("g"))
		{
			layer1.Layer1ToBack(1);
			
		}
		
		//-------//
		
					if (Input.GetKeyDown("y"))
		{
			layer2.Layer1ToFront(2);
		}
		
		if (Input.GetKeyDown("h"))
		{
			layer2.Layer1ToBack(2);
			
		}
		
		//velocidade maxima
		
		//if (gameObject.rigidbody.velocity.magnitude>10)
			//float extravel = gameObject.rigidbody.velocity.magnitude;
		
		
	
	}
}
