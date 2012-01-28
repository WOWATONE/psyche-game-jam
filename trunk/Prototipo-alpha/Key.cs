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
			gameObject.transform.parent = other.gameObject.transform;
		}
	}
}
