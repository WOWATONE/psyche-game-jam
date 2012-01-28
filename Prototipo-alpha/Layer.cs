using UnityEngine;
using System.Collections;

public class Layer : MonoBehaviour {
	
	public int currentPosition;// 0 = back, 1 = front.
	public int layer_number;
	public float depth = 17;

	// Use this for initialization
	void Start () {
		
		//currentPosition = 1;
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void ToFront(int target_layer){
		
		if (target_layer==layer_number)
		{
			if (currentPosition==0)
			{
				gameObject.transform.Translate(0,0,-depth);
				currentPosition=1;
			}
		}
		
	}
	
	public void ToBack(int target_layer){
	if (target_layer==layer_number)
		{	
			if (currentPosition==1)
			{
				gameObject.transform.Translate(0,0,depth);
				currentPosition=0;
			}
		}
		
	}
}
