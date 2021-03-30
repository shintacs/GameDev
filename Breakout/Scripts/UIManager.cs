using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    [SerializeField] GameObject Panel;
    [SerializeField] GameObject GameOverText;
    [SerializeField] GameObject GameClearText;

    BlocksManager blocksmanager;
    EndWallScript endwallscript;

    private bool gameclear;
    //private bool death;
    private bool gameover;

    private int death_cnt;
    //private int life;

    void Start()
    {
        Panel = GameObject.Find("Panel");
        GameOverText = GameObject.Find("GameOverText");
        GameClearText = GameObject.Find("GameClearText");

        blocksmanager = GameObject.Find("Blocks").GetComponent<BlocksManager>();
        endwallscript = GameObject.Find("GameEndWall").GetComponent<EndWallScript>();

        //gameover = false;
        //life = 3;

        ResetUI();
    }

    void Update()
    {
        gameclear = blocksmanager.deleteBlock;
        gameover = endwallscript.hitBall;
        //death = endwallscript.hitBall;
        death_cnt = endwallscript.hitball_cnt;

        print(death_cnt);

        if (gameclear)
        {
            Return2Home();
        }

        /*if (death)
        {
            life = 3 - death_cnt;
            print(life);
        }

        if (life == 0)
        {
            RetryGame();
        }*/

        if (gameover)
        {
            RetryGame();
        }
    }

    public void ResetUI()
    {
        Panel.SetActive(false);
        GameOverText.SetActive(false);
        GameClearText.SetActive(false);
    }

    public void RetryGame()
    {
        Panel.SetActive(true);
        GameOverText.SetActive(true);
        gameclear = false;
    }

    public void Return2Home()
    {
        Panel.SetActive(true);
        GameClearText.SetActive(true);
        gameover = false;
    }
}
