using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    [SerializeField] GameObject Panel;
    [SerializeField] GameObject GameOverText;
    [SerializeField] GameObject GameClearText;
    public BlocksManager blocksmanager;
    public EndWallScript endwallscript;
    private bool gameclear;
    private bool gameover;

    void Start()
    {
        gameclear = blocksmanager.deleteBlock;
        gameover = endwallscript.hitBall;
        Panel = GameObject.Find("Panel");
        GameOverText = GameObject.Find("GameOverText");
        GameClearText = GameObject.Find("GameClearText");

        Panel.SetActive(false);
        GameOverText.SetActive(false);
        GameClearText.SetActive(false);
    }

    void Update()
    {
        if (gameclear)
        {
            RetryGame();
        }

        if (gameover)
        {
            Return2Home();
        }
    }

    public void RetryGame()
    {
        Panel.SetActive(true);
        GameOverText.SetActive(true);

    }

    public void Return2Home()
    {
        Panel.SetActive(true);
        GameClearText.SetActive(true);
    }
}
