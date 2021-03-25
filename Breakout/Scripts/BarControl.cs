using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarControl : MonoBehaviour
{
    private Plane table;
    private Transform bar;
    private bool drag = false;

    void Start()
    {
        var ppos = new Vector3(0, 0.15f, 0);
        table = new Plane(Vector3.up, ppos);
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Raycheck();
        }
        if (drag)
        {
            Dragbar();
        }
        if (Input.GetMouseButtonUp(0))
        {
            drag = false;
        }
    }

    private void Raycheck()
    {
        RaycastHit rayhit;
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(ray, out rayhit, Mathf.Infinity))
        {
            if (rayhit.collider.tag == "Bar")
            {
                drag = true;
                bar = rayhit.transform;
            }
        }
    }

    private void Dragbar()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        float rayDistance;
        table.Raycast(ray, out rayDistance);

        transform.position = new Vector3(ray.GetPoint(rayDistance).x, 0.15f, -4.5f);
        //transform.position = ray.GetPoint(rayDistance);
    }
}
