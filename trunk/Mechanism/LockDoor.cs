using UnityEngine;
using System.Collections;

public class LockDoor : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
	
	}
	
	// Update is called once per frame
	void Update () 
	{
	
	}
	
	void OnTriggerEnter(Collision other)
	{
		if(other.gameObject.CompareTag("Key"))
		{
			//other.gameObject.transform.Translate(0, 0, -30);
			Destroy(gameObject);
			Destroy(other.gameObject);
		}
	}
}
