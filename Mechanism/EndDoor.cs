using UnityEngine;
using System.Collections;
using System.Threading;

public class EndDoor : MonoBehaviour 
{
	public string nextLevel;
	public GameObject textBox;
	public bool transition;
	public int counter;
	
	// Use this for initialization
	void Start() 
	{
		transition = false;
		counter = 0;
	}
	
	// Update is called once per frame
	void Update() 
	{	
		if(transition == true)
		{
			counter++;
			if(counter == 400)
				Application.LoadLevel(nextLevel);
		}
	}
	
	void OnTriggerEnter(Collider other)
	{
		if(other.gameObject.CompareTag("Player"))
		{
			/*Bring TextBox to front*/
			textBox.transform.Translate(0, 0, -33);
			/*Lock and Hide the Player*/
			Destroy(other.gameObject);
			transition = true;
		}
	}
	
	/*void OnTriggerExit(Collider other)
	{
		/*Wait until change of map*/
		
	//}
}
