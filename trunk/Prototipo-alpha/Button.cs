using UnityEngine;
using System.Collections;
using System;

public class Button : MonoBehaviour 
{
	public GameObject target;
	public bool hold;
	public int target_id;
	public int direction=0;//de tras pra frente
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
		{
			if (direction==0)
			target.SendMessage("ToFront",target_id);
			else
			target.SendMessage("ToBack",target_id);
		}
		
		if ((target != null)&&(target.tag=="Player"))
			target.SendMessage("Die");
	}
	
	void OnTriggerExit(Collider other)
	{
		if(hold)
		{
			if((target != null)&&(target.tag=="Block"))
			{			
				if (direction==0)
					target.SendMessage("ToBack",target_id);
				else
					target.SendMessage("ToFront",target_id);
				
			}
		}
	}
}
