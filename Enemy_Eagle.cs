using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_Eagle : Enemy
{
    private Rigidbody2D rb;

    public Transform uppoint, downpoint;
    private float upy, downy;
    public float Speed;

    private bool downfly = true;

    protected override void Start()
    {
        base.Start();
        rb = GetComponent<Rigidbody2D>();
        transform.DetachChildren();
        upy = uppoint.position.y;
        downy = downpoint.position.y;
        Destroy(uppoint.gameObject);
        Destroy(downpoint.gameObject);
    }


    void Update()
    {
        Movement();
    }

    void Movement()
    {
        if(downfly)
        {
            rb.velocity = new Vector2(rb.velocity.x, -Speed);
            if(transform.position.y<downy)
            {
                downfly = false;
            }
        }
        else
        {
            rb.velocity = new Vector2(rb.velocity.x, Speed);
            if (transform.position.y > upy)
            {
                downfly = true;
            }
        }
    }
}
