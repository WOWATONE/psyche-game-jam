using UnityEngine;
using System.Collections;

public class Layer1 : MonoBehaviour {
	
	public int currentPosition;
	public int layer_number;

	// Use this for initialization
	void Start () {
		
		//currentPosition = 1;
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void Layer1ToFront(int target_layer){
		
		if (target_layer==layer_number)
		{
			if (currentPosition==0)
			{
				gameObject.transform.Translate(0,0,1);
				currentPosition=1;
			}
		}
		
	}
	
	public void Layer1ToBack(int target_layer){
	if (target_layer==layer_number)
		{	
			if (currentPosition==1)
			{
				gameObject.transform.Translate(0,0,-1);
				currentPosition=0;
			}
		}
		
	}
}
