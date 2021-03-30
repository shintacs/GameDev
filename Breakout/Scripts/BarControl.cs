using UnityEngine;

public class BarControl : MonoBehaviour
{
    private Plane table;
    private Transform bar;
    private float xpos;
    private bool drag = false;

    void Start()
    {
        var ppos = new Vector3(0, 0.15f, 0);
        table = new Plane(Vector3.up, ppos);
        xpos = 0.01f;
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

        xpos = ray.GetPoint(rayDistance).x; //レイの指す場所のx座標を取得

        if (xpos <= -3.9f)  //ステージ左端にぶつかった場合
        {
            xpos = -3.9f;
        }
        else if(xpos >= 3.6f)   //ステージ右端にぶつかった場合
        {
            xpos = 3.6f;
        }

        transform.position = new Vector3(xpos, 0.15f, -4.5f);
    }
}
