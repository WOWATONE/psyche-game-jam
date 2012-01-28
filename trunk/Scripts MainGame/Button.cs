using UnityEngine;
using System.Collections;
using System;

public class Button : MonoBehaviour 
{
	public GameObject target;
	public bool hold;
	public Layer1 Layer;
	
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
		if(Layer != null)
			Layer.Layer1ToFront(0);
	}
	
	void OnTriggerExit(Collider other)
	{
		if(hold)
		{
			Layer.Layer1ToBack(0);
		}
	}
}
