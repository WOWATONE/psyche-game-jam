using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public float WalkingSpeed = 5;						//Velocidade que o objeto anda
	public float JumpHeight = 100;						//Altura que o Player pula
	public GameObject layer;	
	private bool isJumping = false;				//Player está pulando?
	private string Direction = "Right";			//Armazena o lado para que o player está olhando
	private float WalkingDir;					//Direção em que o player está se movimentando (!= de onde está olhando)

	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () 
	{
		Movement();
	}
	
	void Movement()	
	{
		//Armazena a posição do mouse e faz o player andar de costas caso esteja olhando para a esquerda
		var MousePosition = Input.mousePosition;
		
		if(Input.GetKeyDown("k"))
		{
			layer.SendMessage("ToFront",1);
			
			//l.ToFront(1);
		}
		
		if(Direction == "Right")
			WalkingDir = Input.GetAxis("Horizontal");
		else if(Direction == "Left")
			WalkingDir = -Input.GetAxis("Horizontal");
		
		//Pula caso o botão JUMP for pressionado e se ele já não estiver pulando
		if((Input.GetAxis("Jump") != 0) && Physics.Raycast(transform.position, -transform.up, 5))
		{
			isJumping = true;
			gameObject.rigidbody.AddRelativeForce(transform.up * JumpHeight, ForceMode.Impulse);
			
		}
	    //Movimenta o Player no eixo x utilizando a sua velocidade atual
		//transform.Translate(WalkingDir*WalkingSpeed*Time.deltaTime, 0.0, 0.0);
		gameObject.rigidbody.AddRelativeForce(transform.right * WalkingDir * WalkingSpeed);
	}
}

