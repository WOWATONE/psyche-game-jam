using UnityEngine;
using System.Collections;

public class Wall : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
		gameObject.tag = "Wall";
	}
	
	// Update is called once per frame
	void Update () 
	{
		
	}
	
	void GoDown()
	{
		gameObject.transform.Translate(0, -2, 0);	
	}
	void GoUp()
	{
		gameObject.transform.Translate(0, 2, 0);	
	}
}
