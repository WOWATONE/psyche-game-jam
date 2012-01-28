using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public float WalkingSpeed = 5;				//Velocidade que o objeto anda
	public float JumpSpeed;						//Altura que o Player pula
	public float JumpHeight;
	public Layer1 Layer;	
	private float WalkingDir;					//Direção em que o player está se movimentando (!= de onde está olhando)
	private float gravity;
	private bool isJumping;
	private float JumpHeightAux;
	
	// Use this for initialization
	void Start () {
		gravity = 2000;
		isJumping = false;
	}
	
	// Update is called once per frame
	void Update () 
	{
		Movement();
	}
	
	void Movement()	
	{	
		CharacterController CharController = GetComponent<CharacterController>();
		Vector3 moveDirection = Vector3.zero;
		
		moveDirection = new Vector3(Input.GetAxis("Horizontal"), 0, 0);
		moveDirection = transform.TransformDirection(moveDirection);
		moveDirection *= WalkingSpeed;
		
		//Pula caso o botão JUMP for pressionado e se ele já não estiver pulando
		if((Input.GetAxis("Jump") != 0) && CharController.isGrounded)
		{
			JumpHeightAux = gameObject.transform.position.y + JumpHeight;
			//print(moveDirection.y);
			isJumping = true;
		}
		if(isJumping)
		{
			moveDirection.y += JumpSpeed;
			if(gameObject.transform.position.y > JumpHeightAux)
				isJumping = false;
		}
		else if(!isJumping)
		{
			moveDirection.y -= gravity*Time.deltaTime;
		}
		CharController.Move(moveDirection*Time.deltaTime);
	}
}