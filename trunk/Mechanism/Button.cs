using UnityEngine;
using System.Collections;
using System;

public class Button : MonoBehaviour 
{
	public GameObject target;
	public bool hold;
	
	// Use this for initialization
	void Start () 
	{
		
	}
	
	// Update is called once per frame
	void Update () 
	{
	
	}
	
	void OnTriggerEnter(Collider other)
	{
		if(other.gameObject.CompareTag("Player"))
		{
			if(target.CompareTag("Door"))
			{
				target.SendMessage("Open");
			}
			else if(target.CompareTag("Wall"))
			{
				target.SendMessage("GoDown");
			}
		}
	}
	
	void OnTriggerExit(Collider other)
	{
		if(hold)
		{
			if(other.gameObject.CompareTag("Player"))
			{
				if(target.CompareTag("Door"))
				{
					target.SendMessage("Open");
				}
				else if(target.CompareTag("Wall"))
				{
					target.SendMessage("GoUp");
				}
			}
		}
	}
}
