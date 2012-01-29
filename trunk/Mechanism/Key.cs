using UnityEngine;
using System.Collections;

public class Key : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
		gameObject.tag = "Key";
	}
	
	// Update is called once per frame
	void Update () 
	{
	
	}
	
	void OnTriggerEnter(Collider other)
	{
		print("Passei pela chave");
		
		if(other.gameObject.CompareTag("Player"))
		{
			float x = -20 - gameObject.transform.position.x;
			float y = 80 - gameObject.transform.position.y;
			
			gameObject.transform.Translate(x, y, 0);
			
			other.gameObject.SendMessage("GrabKey", this);
		}
	}
}
