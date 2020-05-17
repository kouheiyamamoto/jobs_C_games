//スティーブ・ジョブスのなんかを作る自由制作課題
//出てきたフルーツを口元まで移動させてリンゴ食べたら嬉しい顔してそれ以外のフルーツだったら嫌な顔するプログラム
//ハンディーグラフィックは必須！

#include <stdio.h>
#include <handy.h>

//defineはなんでも書き換えられる

int main()
{

    int h1;       //鼻のヒゲの何本も出現させる変数
    int h2;       //顎の下の何本も出現させる変数
    int i;        //おまけのカウンタ変数
    int cx = 500; //顔面の中心のx座標
    int cy = 400; //顔面の中心のy座標
    int cr = 200; //顔面の半径
    int g1;       //二段目のぶどう
    int g2;       //三段目のぶどう
    int g3;       //四段目のぶどう
    int n;        //nを変数と置く
    int r = 100;  //りんごの座標
    int ry = 5;   // 速度
    int m;        //みかんの座標
    int g;        //グレープの座標

    HgOpen(1000, 700);

    HgCircle(cx, cy, cr);
    HgLine(450, 300, 550, 300); // 口

    //目ん玉　右
    HgSetFillColor(HG_BLACK);
    HgCircleFill(430, 450, 5, 1);

    //目ん玉　左
    HgSetFillColor(HG_BLACK);
    HgCircleFill(570, 450, 5, 1);

    HgCircle(430, 450, 40);     //メガネのフレーム　右
    HgCircle(570, 450, 40);     //メガネのフレーム 左
    HgLine(470, 450, 530, 450); //メガネのフレーム　真ん中
    HgLine(610, 450, 700, 450); //メガネの線　右
    HgLine(300, 450, 390, 450); //メガネの線　左

    //鼻下ヒゲ　ループで何本も書いてる
    for (h1 = 450; h1 < 550; h1 += 2)
    {
        HgLine(h1, 350, h1, 330);
    }

    //顎下のヒゲ　ループで何本も書いている
    for (h2 = 470; h2 < 530; h2 += 2)
    {
        HgLine(h2, 220, h2, 200);
    }

    printf("1,2,3のなかから何か数字を選んでください:");
    scanf("%d", &n);

    //n = 1だったらリンゴを表示する
    if (n == 1)
    {

        HgCircle(cx, cy, cr);
        HgLine(450, 300, 550, 300); // 口

        //目ん玉　右
        HgSetFillColor(HG_BLACK);
        HgCircleFill(430, 450, 5, 1);

        //目ん玉　左
        HgSetFillColor(HG_BLACK);
        HgCircleFill(570, 450, 5, 1);

        HgCircle(430, 450, 40);     //メガネのフレーム　右
        HgCircle(570, 450, 40);     //メガネのフレーム 左
        HgLine(470, 450, 530, 450); //メガネのフレーム　真ん中
        HgLine(610, 450, 700, 450); //メガネの線　右
        HgLine(300, 450, 390, 450); //メガネの線　左
        HgBox(450, 350, 100, 20);
        HgSetFillColor(HG_GRAY);
        HgCircleFill(430, 450, 5, 1);

        
        //顎下のヒゲ　ループで何本も書いている
        for (h2 = 470; h2 < 530; h2 += 2)
        {
            HgLine(h2, 220, h2, 200);
        }

        for (r = 50; r < 170; r++)
        {
            //clearで一回一回出てくる絵を消す
            //全体の顔
            HgCircle(cx, cy, cr);

            //目ん玉　右
            HgSetFillColor(HG_BLACK);
            HgCircleFill(430, 450, 5, 1);
            //目ん玉　左
            HgSetFillColor(HG_BLACK);
            HgCircleFill(570, 450, 5, 1);
            //メガネのフレーム　右
            HgCircle(430, 450, 40);
            //メガネのフレーム 左
            HgCircle(570, 450, 40);
            //メガネのフレーム　真ん中
            HgLine(470, 450, 530, 450);
            //メガネの線　右
            HgLine(610, 450, 700, 450);
            //メガネの線　左
            HgLine(300, 450, 390, 450);
            //鼻下ヒゲ　ループで何本も書いてる
            for (h1 = 450; h1 < 550; h1 += 2)
            {
                HgLine(h1, 350, h1, 330);
            }
            //顎下のヒゲ　ループで何本も書いている
            for (h2 = 470; h2 < 530; h2 += 2)
            {
                HgLine(h2, 220, h2, 200);
            }
            HgClear();
            HgSetFillColor(HG_RED);
            HgCircleFill(500, r + ry, 20, 1);
            //リンゴの上のついてるやつ
            HgLine(500, r + 10 + ry, 500, r + 30 + ry);
            //ryだけ座標を動かす
            ry += 4;
            HgSleep(0.01);
            //りんごが近づいた時は口が開いてそれ以外の時は口が閉じているプログラム
            if (240 <= r + ry && r + ry <= 580)
            {
                //目はリンゴの時黄色に光る
                //あと口が開く
                HgBox(450, 270, 100, 50);
                //目ん玉右
                HgSetFillColor(HG_YELLOW);
                HgCircleFill(430, 450, 20, 1);

                //目ん玉左
                HgSetFillColor(HG_YELLOW);
                HgCircleFill(570, 450, 20, 1);
                HgSleep(0.01);
                HgSetFont(HG_M, 20);
                HgText(650, 120, "Yes! Steve Jobs！\nアップル社の共同設立者の一人\nアメリカ国家技術賞を受賞している");
            }

            // 修正
            else
            {
                //それ以外の時は目は普通の状態
                HgLine(450, 300, 550, 300);
                //目ん玉右
                HgSetFillColor(HG_BLACK);
                HgCircleFill(430, 450, 5, 1);

                //目ん玉左
                HgSetFillColor(HG_BLACK);
                HgCircleFill(570, 450, 5, 1);
            }
        }

        //この文で繰り返しを終わらせている

        //条件が整ったら特定の文字を表示する
        printf("YES！Steyve jobs\n");
    }

    //n = 2だったらオレンジを表示する
    else if (n == 2)
    {
        //オレンジを動かすためのループ

        //全体の顔
        HgCircle(cx, cy, cr);

        //目ん玉　右
        HgSetFillColor(HG_BLACK);
        HgCircleFill(430, 450, 5, 1);
        //目ん玉　左
        HgSetFillColor(HG_BLACK);
        HgCircleFill(570, 450, 5, 1);
        //メガネのフレーム　右
        HgCircle(430, 450, 40);
        //メガネのフレーム 左
        HgCircle(570, 450, 40);
        //メガネのフレーム　真ん中
        HgLine(470, 450, 530, 450);
        //メガネの線　右
        HgLine(610, 450, 700, 450);
        //メガネの線　左
        HgLine(300, 450, 390, 450);
        //鼻下ヒゲ　ループで何本も書いてる
        for (h1 = 450; h1 < 550; h1 += 2)
        {
            HgLine(h1, 350, h1, 330);
        }
        //顎下のヒゲ　ループで何本も書いている
        for (h2 = 470; h2 < 530; h2 += 2)
        {
            HgLine(h2, 220, h2, 200);
        }

        for (r = 50; r < 170; r++)
        {

            //全体の顔
            HgCircle(cx, cy, cr);

            //目ん玉　右
            HgSetFillColor(HG_BLACK);
            HgCircleFill(430, 450, 5, 1);
            //目ん玉　左
            HgSetFillColor(HG_BLACK);
            HgCircleFill(570, 450, 5, 1);
            //メガネのフレーム　右
            HgCircle(430, 450, 40);
            //メガネのフレーム 左
            HgCircle(570, 450, 40);
            //メガネのフレーム　真ん中
            HgLine(470, 450, 530, 450);
            //メガネの線　右
            HgLine(610, 450, 700, 450);
            //メガネの線　左
            HgLine(300, 450, 390, 450);
            //鼻下ヒゲ　ループで何本も書いてる
            for (h1 = 450; h1 < 550; h1 += 2)
            {
                HgLine(h1, 350, h1, 330);
            }
            //顎下のヒゲ　ループで何本も書いている
            for (h2 = 470; h2 < 530; h2 += 2)
            {
                HgLine(h2, 220, h2, 200);
            }
            //clearで一回一回出てくる絵を消す
            HgClear();

            //オレンジの本体
            HgSetFillColor(HG_ORANGE);
            HgCircleFill(500, r + ry, 20, 1);

            //オレンジの蔕
            HgSetFillColor(HG_GREEN);
            HgCircleFill(500, r + ry + 20, 5, 1);

            //速度の概念でもある
            ry += 4;

            //0.001秒間実行を止める

            //ryだけ座標を動かす
            //近づいた時は口が開いてそれ以外の時は口が閉じているプログラム
            if (240 <= r + ry && r + ry <= 580)
            {
                //口が開く
                HgBox(450, 270, 100, 50);

                //目が線になる
                HgLine(410, 450, 440, 450);
                HgLine(550, 450, 580, 450);
                HgSleep(0.01);
                HgSetFont(HG_M, 20);
                HgText(650, 120, "NO Steve jobs！\nちなみに彼は1985年\n本人の立ち振る舞いが社内を混乱させ\n役職を解任された。");
            }
            //
            else
            {
                //それ以外の時は普通の状態
                HgLine(450, 300, 550, 300);
                HgSetFillColor(HG_BLACK);
                HgCircleFill(430, 450, 5, 1);
                HgSetFillColor(HG_BLACK);
                HgCircleFill(570, 450, 5, 1);
            }
            //この文で繰り返しを終わらせる
        }

        //条件が整ったら特定の文字を表示する
        printf("NO,Steve jobs\n");
    }

    //n = 3だったらぶどうを表示する
    else if (n == 3)
    {
        //全体の顔
        HgCircle(cx, cy, cr);

        //目ん玉　右
        HgSetFillColor(HG_BLACK);
        HgCircleFill(430, 450, 5, 1);
        //目ん玉　左
        HgSetFillColor(HG_BLACK);
        HgCircleFill(570, 450, 5, 1);
        //メガネのフレーム　右
        HgCircle(430, 450, 40);
        //メガネのフレーム 左
        HgCircle(570, 450, 40);
        //メガネのフレーム　真ん中
        HgLine(470, 450, 530, 450);
        //メガネの線　右
        HgLine(610, 450, 700, 450);
        //メガネの線　左
        HgLine(300, 450, 390, 450);
        //鼻下ヒゲ　ループで何本も書いてる
        for (h1 = 450; h1 < 550; h1 += 2)
        {
            HgLine(h1, 350, h1, 330);
        }
        //顎下のヒゲ　ループで何本も書いている
        for (h2 = 470; h2 < 530; h2 += 2)
        {
            HgLine(h2, 220, h2, 200);
        }

        for (r = 50; r < 170; r++)
        {
            //全体の顔
            HgCircle(cx, cy, cr);

            //目ん玉　右
            HgSetFillColor(HG_BLACK);
            HgCircleFill(430, 450, 5, 1);
            //目ん玉　左
            HgSetFillColor(HG_BLACK);
            HgCircleFill(570, 450, 5, 1);
            //メガネのフレーム　右
            HgCircle(430, 450, 40);
            //メガネのフレーム 左
            HgCircle(570, 450, 40);
            //メガネのフレーム　真ん中
            HgLine(470, 450, 530, 450);
            //メガネの線　右
            HgLine(610, 450, 700, 450);
            //メガネの線　左
            HgLine(300, 450, 390, 450);
            //鼻下ヒゲ　ループで何本も書いてる
            for (h1 = 450; h1 < 550; h1 += 2)
            {
                HgLine(h1, 350, h1, 330);
            }
            //顎下のヒゲ　ループで何本も書いている
            for (h2 = 470; h2 < 530; h2 += 2)
            {
                HgLine(h2, 220, h2, 200);
            }
            //clearで一回一回出てくる絵を消す
            HgClear();
            //ぶどうの描写

            //ぶどう一段目
            HgSetFillColor(HG_PURPLE);
            HgCircleFill(500, r + ry, 5, 1);

            //ぶどう二段目
            for (g1 = 495; g1 <= 505; g1 += 10)
            {
                HgSetFillColor(HG_PURPLE);
                HgCircleFill(g1, r + ry + 7, 5, 1);
            }

            //ぶどう三段目
            for (g2 = 490; g2 <= 510; g2 += 10)
            {
                HgSetFillColor(HG_PURPLE);
                HgCircleFill(g2, r + ry + 12, 5, 1);
            }

            //ぶどう四段目
            for (g3 = 485; g3 <= 515; g3 += 10)
            {
                HgSetFillColor(HG_PURPLE);
                HgCircleFill(g3, r + ry + 19, 5, 1);
            }

            //0.001秒間実行を止める

            //ryだけ座標を動かす
            //速度の概念でもある
            ry += 4;
            //口
            //近づいた時は口が開いてそれ以外の時は口が閉じているプログラム
            if (240 <= r + ry && r + ry <= 580)
            {
                //口が開く
                HgBox(450, 270, 100, 50);
                //目が線になる
                HgLine(410, 450, 440, 450);
                HgLine(550, 450, 580, 450);
                HgSleep(0.01);
                HgSetFont(HG_M, 20);
                HgText(650, 120, "スティーブ・ジョブスの名言\nStay hungry Stay foolish.\nハングリーであれ。おろかものであれ。\nという名言を残した。");
            }
            // 修正
            else
            {
                HgLine(450, 300, 550, 300);
                HgSetFillColor(HG_BLACK);
                HgCircleFill(430, 450, 5, 1);
                HgSetFillColor(HG_BLACK);
                HgCircleFill(570, 450, 5, 1);
            }
            //この文で繰り返しを終わらせている
        }

        //条件が整ったら文字を表示する
        printf("NO,steve jobs\n");

        //どうやったら1入力した時に終了できるのか？
    }

    //ハンディーをどっかで終了させないといけない
    HgGetChar();
    HgClose();

    return 0;
}
