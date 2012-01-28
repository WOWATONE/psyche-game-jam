using UnityEngine;
using System.Collections;
using System.Threading;

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
	
	void OnTriggerEnter(Collider other)
	{
		if(other.gameObject.CompareTag("Player"))
		{
			/*Bring TextBox to front*/
			textBox.transform.Translate(0, 0, 33);
			
			
			/*Wait until change of map*/
			Thread.Sleep(3000);	
			Application.LoadLevel(nextLevel);
		}
	}
}
