using UnityEngine;
using System.Collections;

public class LockDoor : MonoBehaviour 
{
	public Player player;
	
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
		print("Bati na Porta");
		
		if(other.gameObject.CompareTag("Player"))
		{
			if(player.countKeys > 0)
			{
				gameObject.transform.Translate(0, 0, -25);
				Destroy(player.key.gameObject);
				player.countKeys--;
			}
			
			print("Entrei na Porta");
		}
	}
	
}
