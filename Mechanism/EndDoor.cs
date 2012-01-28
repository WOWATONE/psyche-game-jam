using UnityEngine;
using System.Collections;

public class EndDoor : MonoBehaviour 
{
	public string nextLevel;
	public GameObject textBox;
	
	// Use this for initialization
	void Start() 
	{
		
	}
	
	// Update is called once per frame
	void Update() 
	{
		
	}
	
	void OnTriggerEnter(Collision other)
	{
		if(other.gameObject.CompareTag("Player"))
		{
			/*Bring TextBox to front*/
			textBox.transform.translate(0, 0, 33);
			
			
			/*Wait until change of map*/
			Thread.Sleep(3000);	
			Application.LoadLevel(nextLevel);
		}
	}
}
