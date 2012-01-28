using UnityEngine;
using System.Collections;
using System;

public class Button : MonoBehaviour 
{
	public GameObject target;
	public bool hold;
	public int target_id;
	//public Layer1 Layer;
	
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
		if((target != null)&&(target.tag=="Block"))
			target.SendMessage("ToFront",target_id);
	}
	
	void OnTriggerExit(Collider other)
	{
		if(hold)
		{
			if((target != null)&&(target.tag=="Block"))
				target.SendMessage("ToBack",target_id);
		}
	}
}
