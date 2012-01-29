using UnityEngine;
using System.Collections;

public class Shadow : MonoBehaviour 
{
	public int destX;
	public int arriveDir;	//1 = right, 0 = left
	public TextBox target;
	private int speed;
	
	// Use this for initialization
	void Start () 
	{
		speed = 4;
	}
	
	// Update is called once per frame
	void Update () 
	{
		int x = gameObject.transform.position.x;
		
		/*Bring Shadow to Scene*/
		if(x != destX)
		{
			if(arriveDir == 0)
				x -= speed;
			else
				x += speed;
			
			gameObject.transform.Translate(destX - x, 0, 0);
			target.SendMessage("ToFront", 0);
		}
		
		/*Check if he is already seen and go back*/
		if(target.currentPosition == 1)
		{
			if(arriveDir == 0 && x < 150)
				x += speed;
			else if(arriveDir == 1 && x > -150)
				x -= speed;
				
			gameObject.transform.Translate(destX - x, 0, 0);
			//target.SendMessage("FadeOut");
		}
	}
}
