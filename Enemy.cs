using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour  //制作父类
{
    protected Animator Anim;
    protected AudioSource deathAudio;

    protected virtual void Start()
    {
        Anim = GetComponent<Animator>();
        deathAudio = GetComponent<AudioSource>();
    }
    public void Death()
    {
        Destroy(gameObject);
    }
    public void JumpOn()
    {
        Anim.SetTrigger("death");
        deathAudio.Play();
    }
}

