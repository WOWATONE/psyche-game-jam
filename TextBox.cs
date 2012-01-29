using UnityEngine;
using System.Collections;

public class TextBox : MonoBehaviour
{
	public int currentPosition = 0;// 0 = back, 1 = front.
	public float depth = 20;
	private int counter = 0;
	public int delay = 400;
	
	// Use this for initialization
	void Start () 
	{
	
	}
	
	// Update is called once per frame
	void Update ()
	{
		if(currentPosition == 1) //on front
		{
			counter++;
			if(counter == delay)
				FadeOut();
		}
	}
	
	public void ToFront(int target_layer)
	{
		if (currentPosition == 0)
		{
			gameObject.transform.Translate(0,0,-depth);
			currentPosition = 1;
		}
	}
	
	public void FadeOut()
	{
		if (currentPosition == 1)
		{
			gameObject.transform.Translate(0,0,depth);
			currentPosition = 0;
		}
	}
}
