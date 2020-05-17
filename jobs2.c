// 画面に出ているジョブズの顔を操作して、ランダムで降ってくる
// りんご、みかん、ぶどうの三つの中から、りんごを食ったら顔がまたキラリと光り、
// それ以外を食べたら、嫌な顔をする
// 今回はただ食わせるだけでなく、りんごを食べたら得点をプラス、
// それ以外を食べたら得点をマイナスするようなプログラムを作る
// で最終的にプレイ後の得点を表示してみんなが楽しめるゲームを作る

// まずなんぼかのウインドウを表示させて、
// エンターキーを押したらゲームがスタートして、
// 徐々にりんご、みかん、ぶどうのどれかがランダムに降ってくる
// それをジョブズを動かしてなんとかりんごを食べようとする。

/* 参考URL https://www.myinstants.com/instant/windows-xp-shutdown/ ( マイクロソフトシャットダウン時の音源　)
          https://www.google.com/imgres?imgurl=https%3A%2F%2Fc.s-microsoft.com%2Fja-jp%2FCMSImages%2Fcorplogo_img_01.gif%3Fversion%3Dab2e8a9a-489b-69b9-836f-7e6061bbcd5c&imgrefurl=https%3A%2F%2Fwww.microsoft.com%2Fja-jp%2Fmscorp%2Flegal%2Ftrademarks%2Fcorplogo.aspx&docid=e2BOIkqdehEEzM&tbnid=saj8au4oIR2D9M%3A&vet=10ahUKEwjUg9PsjLXfAhXFu7wKHf5uAkAQMwg_KAAwAA..i&w=250&h=93&bih=789&biw=1440&q=%E3%83%9E%E3%82%A4%E3%82%AF%E3%83%AD%E3%82%BD%E3%83%95%E3%83%88%20%E3%83%AD%E3%82%B4&ved=0ahUKEwjUg9PsjLXfAhXFu7wKHf5uAkAQMwg_KAAwAA&iact=mrc&uact=8
          （ マイクロソフトのロゴデザインとして参考資料　） */

#include <stdio.h>
#include <handy.h>
#include <stdlib.h> // この中に乱数を返すrand関数があった
#include <time.h>   // 時間をとる関数が入っている
#include <math.h>   // ルートの計算をするための標準ファイル

#define WH 1100   // ウインドウの縦のサイズ
#define WS 700    // ウインドウの横のサイズ
#define FK 5      // 落ちてくるフルーツの数
#define AK 3      // 落ちてくる特殊アイテムの数
#define AT 100.0  // appleとった時の得点
#define OGT -50.0 // orange, grapeとった時の得点
#define AHT 90.0  // 当たり判定の距離
#define MHT 80.0  // マイクロソフトの当たり判定
#define JX 550    // ジョブズの顔のx座標
#define Y 265     // ジョブズの顔のy座標
#define AX 90     // appleの顔のx座標
#define OX 285    // orangeのx座標
#define GX 360   // grapeのx座標
#define PX 730    // ipodのx座標
#define PY 235    // ipodのx座標
#define MX 960    // ipodのx座標
#define MY 265    // ipodのx座標

// 関数のプロトタイプ宣言
void jobs(); // ジョブズの顔用の関数

void apple(); // appleの描画用の関数

void orange(); // orangeの描画用の関数

void grape(); // grapeの描画用の関数

void microsoft(); // microsoft用の関数

void microsoftnr(); // 右斜めから降ってくるmicrosoft用の関数

void microsoftnl(); // 左斜めから降ってくるmicrosoft用の関数

void ipod(); // ipod描画用の関数

void tentionupjobs(); // appleをとった時のジョブズの描画用の関数

void tentiondownjobs(); // orangeもしくはgrapeをとった時のジョブズの描画用の関数

void jobsimage(); // ジョブズの画像を読み込むための関数

void geaituimage(); // ジョブズの画像を読み込むための関数

// ここに書けばグローバル変数
doubleLayer layers; // ダブルレイヤの変数を宣言する
int layer1;         // レイヤを追加する

int main()
{
    // ループの中で使用するフラグたち
    int upjobs = 0;   // ジョブズが喜んだ時のフラグ
    int downjobs = 0; // ジョブズが落ち込んだときの顔を表示するためのフラグ
    int supjobs = 0;  // ジョブズがスピードupする時のフラグ
    int sup = 0;      // ipodをとったことを表示するためのフラグ

    double startTime;       // 始まった時の時間
    double endTime;         // 終わった時の時間
    double totalTime = 0.0; // endtime - starttime
    double setTime = 0.0;   // 何秒間処理するかの時間を格納するための変数

    // 各アイテムのx座標を格納するための配列
    double ax[FK] = {}; // appleのx座標
    double ox[FK] = {}; // orangeのx座標
    double gx[FK] = {}; // grapeのx座標
    double mx[AK] = {}; // microsoftのx座標
    double px[AK] = {}; // ipodのx座標

    // 各アイテムのy座標を格納するための配列
    double ay[FK] = {}; // appleのy座標
    double oy[FK] = {}; // orangeのy座標
    double gy[FK] = {}; // grapeのy座標
    double my[AK] = {}; // microsoftのy座標
    double py[AK] = {}; // ipodのy座標

    // 各アイテムの落下スピードを格納する配列
    double ayy[FK] = {}; // appleのスピード
    double oyy[FK] = {}; // orangeのスピード
    double gyy[FK] = {}; // grapeのスピード　
    double myy[AK] = {}; // microsoftのスピード
    double pyy[AK] = {}; // ipodのスピード

    // 斜めようの変数
    double mxnr[2] = {}; // 右斜め上の座標
    double mxnl[2] = {}; // 左斜め上の座標
    double myn[2] = {};  // 右左両方のy座標
    double mxns[2] = {}; // x座標の移動のスピード
    double myns[2] = {}; // y座標の移動のスピード

    double jx = 550; // ジョブズの顔のx座標
    double tuj;      // テンション上がった時のジョブズ
    double tdj;      // テンション下がった時のジョブズ

    double t; // 得点をカウントする用の変数

    int count = 0; // 一度立てたフラグを元に戻すための変数

    int img = HgImageLoad("jobs1.jpg"); // ジョブズの画像を読み込んで変数に代入
    int img2 = HgImageLoad("geaitu.jpg"); // ゲイツの画像を読み込んで変数に代入

    //ランダムに数字を代入する処理
    srand(time(NULL));
    for (int i = 0; i < FK; i++)
    {
        // 各アイテムのx座標を乱数でとる
        ax[i] = (rand() % 1050) + 50;
        ox[i] = (rand() % 1050) + 50;
        gx[i] = (rand() % 1050) + 50;

        // 各アイテムのy座標を乱数でとる
        ay[i] = (rand() % 2500) + 1200;
        oy[i] = (rand() % 2500) + 1200;
        gy[i] = (rand() % 2500) + 1200;

        // 各アイテムの落下スピードを乱数でとる
        ayy[i] = (rand() % 30) + 15;
        oyy[i] = (rand() % 30) + 15;
        gyy[i] = (rand() % 30) + 15;
    }

    // マイクロソフトとipodは出てくる数が違うから、別のところで乱数をとる
    srand(time(NULL));
    for (int i = 0; i < AK; i++)
    {
        mx[i] = (rand() % 1050) + 50;
        px[i] = (rand() % 1050) + 50;

        my[i] = (rand() % 2500) + 1200;
        py[i] = (rand() % 2500) + 1200;

        myy[i] = (rand() % 30) + 15;
        pyy[i] = (rand() % 30) + 15;
    }

    // 斜めのマイクロソフトの座標をランダムでとる
    srand(time(NULL));
    for (int i = 0; i < 2; i++)
    {
        mxnr[i] = (rand() % 1300) + 1200; // 右斜め上の座標
        mxnl[i] = (rand() % -100) + -200; // 左斜め上の座標
        myn[i] = (rand() % 1200) + 1100;  // 右左両方のy座標
        mxns[i] = (rand() % 30) + 15;     // x座標の移動のスピード
        myns[i] = (rand() % 30) + 15;     // y座標の移動スピード
    }

    setTime = 30.0;
    setTime *= 10;

    HgOpen(WH, WS); // ウインドウを開く

    HgSetTitle("帰ってきたジョブズ"); // ウインドウに名前を付ける

    jobsimage(layer1, img);

    HgSetFont(HG_GB, 80); // Bつけたら太字になる
    HgWSetColor(layer1, HG_RED);
    HgWText(layer1, 210, 610, "The life of jobs");

    HgSetFont(HG_G, 35); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 105, 530, "上から降ってくるいろんな物の中からできる限り");

    HgSetFont(HG_G, 35); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 115, 480, "りんごを多くとって得点を稼ごう！");

    HgSetFont(HG_G, 40); // Bつけたら太字になる
    HgWSetColor(layer1, HG_CYAN);
    HgWText(layer1, 70, 370, "キャラクター　& アイテム紹介");

    HgWSetColor(layer1, HG_BLACK);

    // こっからはジョブズの顔
    HgWCircle(layer1, JX, Y, 55);

    HgWLine(layer1, JX - 20, Y - 40, JX + 20, Y - 40); //口

    // 目ん玉　右
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, JX + 20, Y + 10, 3, 1);

    // 目ん玉　左
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, JX - 20, Y + 10, 3, 1);
    HgWCircle(layer1, JX + 20, Y + 10, 13); //メガネのフレーム　右

    HgWCircle(layer1, JX - 20, Y + 10, 13); //メガネのフレーム 左

    HgWLine(layer1, JX - 7, Y + 10, JX + 7, Y + 10); //メガネのフレーム　真ん中

    HgWLine(layer1, JX + 33, Y + 10, JX + 55, Y + 10); //メガネの線　右

    HgWLine(layer1, JX - 55, Y + 10, JX - 33, Y + 10); //メガネの線　左

    // 鼻下のヒゲ
    HgWSetFillColor(layer1, HG_GRAY);
    HgWBoxFill(layer1, JX - 20, Y - 20, 40, 7, 0);

    // 顎下のヒゲ
    HgWSetFillColor(layer1, HG_GRAY);
    HgWBoxFill(layer1, JX - 10, Y - 54, 20, 5, 0);

    // 説明
    HgSetFont(HG_G, 15); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 500, 140, "操作キャラ\nおなじみ\nあのSteve Jobs");

    // apple
    HgWSetFillColor(layer1, HG_RED);
    HgWCircleFill(layer1, AX, Y, 20, 1);
    // リンゴの上のついてるやつ
    HgWLine(layer1, AX, 10 + Y, AX, 30 + Y);

    // 説明
    HgSetFont(HG_G, 15); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 60, 130, "おなじみの\napple\n取ると\n点数が＋100");

    // orange
    HgWSetFillColor(layer1, HG_ORANGE);
    HgWCircleFill(layer1, OX, Y, 20, 1);
    // オレンジの蔕
    HgWSetFillColor(layer1, HG_GREEN);
    HgWCircleFill(layer1, OX, Y + 20, 5, 1);

    // grape
    // ぶどう一段目
    HgWSetFillColor(layer1, HG_PURPLE);
    HgWCircleFill(layer1, GX, Y, 5, 1);

    //ぶどう二段目
    for (int g1 = GX - 5; g1 <= GX + 5; g1 += 10)
    {
        HgWSetFillColor(layer1, HG_PURPLE);
        HgWCircleFill(layer1, g1, Y + 7, 5, 1);
    }

    //ぶどう三段目
    for (int g2 = GX - 10; g2 <= GX + 10; g2 += 10)
    {
        HgWSetFillColor(layer1, HG_PURPLE);
        HgWCircleFill(layer1, g2, Y + 12, 5, 1);
    }

    // 説明
    HgSetFont(HG_G, 15); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 280, 142, "orangeとgrapeは\nどちらも取ると\n点数が-50");

    // ipod
    HgWSetFillColor(layer1, HG_CYAN);
    HgWBoxFill(layer1, PX, PY, 54, 70, 1);

    HgWSetFillColor(layer1, HG_BLACK);
    HgWBoxFill(layer1, PX + 7, PY + 25, 40, 40, 1);

    HgWSetFillColor(layer1, HG_WHITE);
    HgWCircleFill(layer1, PX + 27, PY + 12, 10, 1);

    HgWSetFillColor(layer1, HG_CYAN);
    HgWCircleFill(layer1, PX + 27, PY + 12, 5, 1);

    // 説明
    HgSetFont(HG_G, 15); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 715, 142, "スペシャルアイテム!(良)\n取ると\njobsのスピードがupする");

    // microsoft
    HgWSetFillColor(layer1, HG_BLUE);
    HgWBoxFill(layer1, MX - 55, MY - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_YELLOW);
    HgWBoxFill(layer1, MX + 1, MY - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_RED);
    HgWBoxFill(layer1, MX - 55, MY + 1, 54, 49, 0);

    HgWSetFillColor(layer1, HG_GREEN);
    HgWBoxFill(layer1, MX + 1, MY + 1, 54, 49, 0);

    // 説明
    HgSetFont(HG_G, 15); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 910, 142, "スペシャルアイテム!(悪)\n取ると\nまさかの...");

    HgSetFont(HG_G, 25); // Bつけたら太字になる
    HgWSetColor(layer1, HG_BLACK);
    HgWText(layer1, 690, 30, "何かキーを押すとゲームスタート！");

    // イベントをするための種類を選ぶ
    HgWSetEventMask(layer1, HG_KEY_DOWN);

    // イベントをするために関数化
    hgevent *event = HgEvent();

    // もしも何かキーが押されたら
    if (event->type == HG_KEY_DOWN)
    {
        HgLClear(layer1);
    }

    layer1 = HgWAddLayer(0);       // ウインドウにレイヤーを追加する
    layers = HgWAddDoubleLayer(0); // ダブルレイヤを追加する

    /* タイマー開始（ミリ秒単位） */
    startTime = clock() / CLOCKS_PER_SEC;

    // メインプレイ画面での無限ループの処理
    while (1) // １５秒間動作を続ける
    {
        // ダブルバッファリング
        layer1 = HgLSwitch(&layers);
        HgLClear(layer1);

        HgWLine(layer1, 950, 700, 950, 630); // カウントの縦の線

        HgWLine(layer1, 950, 630, 1100, 630); // カウントの横の線

        // セットした時間が経過したら終了する
        if (totalTime > setTime)
            break;
        endTime = clock() / CLOCKS_PER_SEC; // endtimeをclock関数化
        totalTime = endTime - startTime;

        HgSetFont(HG_G, 35);                              // Bつけたら太字になる
        HgWText(layer1, 995, 650, "%1.1f", setTime / 10); // 時間を表示する

        setTime--; // timeをカウントダウン方式にしておく

        // appleとった時のジョブズ
        if (upjobs == 1)
        {
            tentionupjobs(jx);
            HgWSetFont(layer1, HG_G, 30); // 文字の大きさとかフォントの種類設定するやつ
            HgWText(layer1, 910, 150, "Jobs！");
            count++;
        }

        // orage,grapeとった時のジョブズ
        else if (downjobs == 1)
        {
            tentiondownjobs(jx);
            HgWSetFont(layer1, HG_G, 30); // 文字の大きさとかフォントの種類設定するやつ
            HgWText(layer1, 910, 340, "Not Jobs！");
            count++;
        }

        // それ以外はジョブズを表示
        else
        {
            jobs(jx);
        }

        // countが１０になったらフラグを元に戻す
        if (count == 10)
        {
            upjobs = 0;
            downjobs = 0;
            sup = 0;
            count = 0;
        }

        // ジョブズを右、左に動かす
        hgevent *event = HgEventNonBlocking(); // 処理をブロックしない方法
        if (event != NULL)                     // なんかした時に同時に処理できるようにするのがHgNonBlocking
        {
            if (event->ch == HG_R_ARROW)
            {
                if ( jx < 1100 )
                jx += 20;
            }
            if (event->ch == HG_L_ARROW)
            {
                if ( jx > 0 )
                jx -= 20;
            }
        }

        // 配列をapple,orage,grapeの当たり判定
        for (int i = 0; i < FK; i++)
        {
            apple(ax[i], ay[i]);
            orange(ox[i], oy[i]);
            grape(gx[i], gy[i]);

            // jobsとアイテムの中心座標同士の距離判定
            double dia = pow(ax[i] - jx, 2.0) + pow(ay[i] - 70.0, 2.0), dia_result; // pow関数はなんとかの２乗とかの計算をする
            dia_result = sqrt(dia);                                                 // sqrt関数は平方根を計算する

            double dio = pow(ox[i] - jx, 2.0) + pow(oy[i] - 70.0, 2.0), dio_result; // pow関数はなんとかの２乗とかの計算をする
            dio_result = sqrt(dio);                                                 // sqrt関数は平方根を計算する

            double dig = pow(gx[i] - jx, 2.0) + pow(gy[i] - 70.0, 2.0), dig_result; // pow関数はなんとかの２乗とかの計算をする
            dig_result = sqrt(dig);                                                 // sqrt関数は平方根を計算する

            // appleが当たり判定内に来た時upjobsのフラグを立てる
            if (dia_result <= AHT)
            {
                upjobs = 1;
                t += AT; // 得点をプラス
            }
            // orange、grapeが来た時downjobsのフラグを立てる
            else if (dio_result <= AHT || dig_result <= AHT)
            {
                downjobs = 1;
                t += OGT;
            }

            ay[i] -= ayy[i];
            oy[i] -= oyy[i];
            gy[i] -= gyy[i];

            // 落ちてきたitemが下まできたら上に戻す処理
            if (ay[i] < 50)
            {
                ax[i] = (rand() % 1050) + 50;
                ay[i] = 1500;
            }
            if (oy[i] < 50)
            {
                ox[i] = (rand() % 1050) + 50;
                oy[i] = 1500;
            }
            if (gy[i] < 50)
            {
                gx[i] = (rand() % 1050) + 50;
                gy[i] = 1500;
            }
        }

        // マイクロソフトとipodの場合の当たり判定
        for (int i = 0; i < AK; i++)
        {
            microsoft(mx[i], my[i]);
            ipod(px[i], py[i]);

            // マイクロソフトとジョブズの距離判定
            double dim = pow(mx[i] - jx, 2.0) + pow(my[i] - 70.0, 2.0), dim_result; // pow関数はなんとかの２乗とかの計算をする
            dim_result = sqrt(dim);

            // 斜めからくるマイクロソフトとジョブズの距離判定
            double dimnr = pow(mxnr[i] - jx, 2.0) + pow(myn[i] - 70.0, 2.0), dimnr_result; // pow関数はなんとかの２乗とかの計算をする
            dimnr_result = sqrt(dimnr);

            // 斜めからくるマイクロソフトとジョブズの距離判定
            double dimnl = pow(mxnl[i] - jx, 2.0) + pow(myn[i] - 70.0, 2.0), dimnl_result; // pow関数はなんとかの２乗とかの計算をする
            dimnl_result = sqrt(dimnl);                                                    // sqrt関数は平方根を計算する

            // ipodとジョブズの距離判定
            double dip = pow(px[i] - jx, 2.0) + pow(py[i] - 70.0, 2.0), dip_result; // pow関数はなんとかの２乗とかの計算をする
            dip_result = sqrt(dip);                                                 // sqrt関数は平方根を計算する

            // マイクロソフトに当たった時は、ゲームを終了する
            if ((dim_result <= MHT) || (dimnr_result <= MHT) || (dimnl_result <= MHT))
            {
                // 音を鳴らす処理
                hgsound sid = HgSoundLoad("windowssound3.mp3");
                HgSoundVolume(sid, 0.5, 0);
                HgSoundPlay(sid);
                HgWText(layer1, 580, 300, "マイク□ソフトに当たった");
                HgSleep(3.0);

                // 音がなってから終了画面に行く処理
                HgClear();
                geaituimage(img2);
                HgSetFont(HG_GB, 60); // Bつけたら太字になる
                HgSetColor(HG_RED);
                HgText(120, 450, "あなたはマイクロソフトにやられた");
                HgSetFont(HG_GB, 60); // Bつけたら太字になる
                HgSetColor(HG_CYAN);
                HgText(120, 250, "あなたの得点は%3.1f点！", t);
                HgSleep(3.0);

                HgGetChar();
                HgClose();
                return 0;
            }

            // ipodの時は、jobsのスピードをupする
            else if (dip_result <= AHT)
            {
                supjobs = 1;
                sup = 1;
            }

            // ipodをとった時のフラグ
            else if (sup == 1)
            {
                HgWSetFont(layer1, HG_G, 30); // 文字の大きさとかフォントの種類設定するやつ
                HgWText(layer1, 580, 250, "ipod get jobs speed up！");
                count++;
            }

            // ipodをとった時のフラグ
            else if (supjobs == 1)
            {
                hgevent *event = HgEventNonBlocking(); // 処理をブロックしない方法
                if (event != NULL)                     // なんかした時に同時に処理できるようにするのがHgNonBlocking
                {                                      // ipodをとったらジョブズのスピードがアップ
                    // スピードが４アップ
                    if (event->ch == HG_R_ARROW)
                    {
                        if ( jx < 1100 )
                        jx += 24;
                    }
                    if (event->ch == HG_L_ARROW)
                    {
                        if ( jx > 0 )
                        jx -= 24;
                    }
                }
            }

            if (count == 10)
            {
                sup = 0;
                count = 0;
            }

            my[i] -= myy[i];
            py[i] -= pyy[i];

            if (my[i] < 50) // y座標が５０以下になったら座標を上に戻す
            {
                mx[i] = (rand() % 1050) + 50;
                my[i] = 1500;
            }

            if (py[i] < 50) // y座標が５０以下になったら座標を上に戻す
            {
                px[i] = (rand() % 1050) + 50;
                py[i] = 1500;
            }
        }

        // 斜めから振ってくるマイクロソフトの数を増やすためのループ
        for (int i = 0; i < 2; i++)
        {
            microsoftnr(mxnr[i], myn[i]);
            microsoftnl(mxnl[i], myn[i]);

            mxnr[i] -= mxns[i];
            mxnl[i] -= mxns[i];
            myn[i] -= myns[i];

            if (myn[i] < 50) // y座標が５０以下になったら座標を上に戻す
            {
                mxnr[i] = (rand() % 1400) + 1200;
                mxnl[i] = (rand() % -100) + -300;
                myn[i] = (rand() % 1200) + 1100;
            }
        }
        HgSleep(0.1);
    }

    // ３コマ目での処理
    HgClear();
    HgSetFont(HG_GB, 80); // Bつけたら太字になる
    HgSetColor(HG_RED);
    HgText(240, 450, "終了！");
    HgSetFont(HG_GB, 80); // Bつけたら太字になる
    HgSetColor(HG_CYAN);
    HgText(120, 300, "あなたの得点は%3.1f点！", t);
    HgSleep(3.0);

    HgGetChar();
    HgClose();
    return 0;
}

// ジョブズの描画の関数
void jobs(double jx)
{
    // こっからはジョブズの顔
    HgWCircle(layer1, jx, 70, 55);

    //口
    HgWLine(layer1, jx - 20, 30, jx + 20, 30);

    // 目ん玉　右
    // ２個目のウインドウに描くときは、HgWC
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, jx + 20, 80, 3, 1);

    // 目ん玉　左
    // ２個目のウインドウに描くときは、HgWC
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, jx - 20, 80, 3, 1);
    //メガネのフレーム　右
    HgWCircle(layer1, jx + 20, 80, 13);
    //メガネのフレーム 左
    HgWCircle(layer1, jx - 20, 80, 13);
    //メガネのフレーム　真ん中
    HgWLine(layer1, jx - 7, 80, jx + 7, 80);
    //メガネの線　右
    HgWLine(layer1, jx + 33, 80, jx + 55, 80);
    //メガネの線　左
    HgWLine(layer1, jx - 55, 80, jx - 33, 80);

    // 鼻下のヒゲ
    HgWSetFillColor(layer1, HG_GRAY);
    HgWBoxFill(layer1, jx - 20, 50, 40, 7, 0);

    // 顎下のヒゲ
    HgWSetFillColor(layer1, HG_GRAY);
    HgWBoxFill(layer1, jx - 10, 16, 20, 5, 0);
}

// アップルの描画の関数
void apple(double ax, double ay)
{
    HgWSetFillColor(layer1, HG_RED);
    HgWCircleFill(layer1, ax, ay, 20, 1);
    // リンゴの上のついてるやつ
    HgWLine(layer1, ax, 10 + ay, ax, 30 + ay);
}

// オレンジの描画の関数
void orange(double ox, double oy)
{
    HgWSetFillColor(layer1, HG_ORANGE);
    HgWCircleFill(layer1, ox, oy, 20, 1);
    // オレンジの蔕
    HgWSetFillColor(layer1, HG_GREEN);
    HgWCircleFill(layer1, ox, oy + 20, 5, 1);
}

// グレープの描画の関数
void grape(double gx, double gy)
{
    // ぶどう一段目
    HgWSetFillColor(layer1, HG_PURPLE);
    HgWCircleFill(layer1, gx, gy, 5, 1);

    //ぶどう二段目
    for (int g1 = gx - 5; g1 <= gx + 5; g1 += 10)
    {
        HgWSetFillColor(layer1, HG_PURPLE);
        HgWCircleFill(layer1, g1, gy + 7, 5, 1);
    }

    //ぶどう三段目
    for (int g2 = gx - 10; g2 <= gx + 10; g2 += 10)
    {
        HgWSetFillColor(layer1, HG_PURPLE);
        HgWCircleFill(layer1, g2, gy + 12, 5, 1);
    }
}

// マイクロソフトの描画の関数
void microsoft(double mx, double my)
{
    HgWSetFillColor(layer1, HG_BLUE);
    HgWBoxFill(layer1, mx - 55, my - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_YELLOW);
    HgWBoxFill(layer1, mx + 1, my - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_RED);
    HgWBoxFill(layer1, mx - 55, my + 1, 54, 49, 0);

    HgWSetFillColor(layer1, HG_GREEN);
    HgWBoxFill(layer1, mx + 1, my + 1, 54, 49, 0);
}

// 右斜め上から降ってくるマイクロソフトの描画の関数
void microsoftnr(double mxnr, double myn)
{
    HgWSetFillColor(layer1, HG_BLUE);
    HgWBoxFill(layer1, mxnr - 55, myn - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_YELLOW);
    HgWBoxFill(layer1, mxnr + 1, myn - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_RED);
    HgWBoxFill(layer1, mxnr - 55, myn + 1, 54, 49, 0);

    HgWSetFillColor(layer1, HG_GREEN);
    HgWBoxFill(layer1, mxnr + 1, myn + 1, 54, 49, 0);
}

// 左斜め上から降ってくるマイクロソフトの描画の関数
void microsoftnl(double mxnl, double myn)
{
    HgWSetFillColor(layer1, HG_BLUE);
    HgWBoxFill(layer1, mxnl - 55, myn - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_YELLOW);
    HgWBoxFill(layer1, mxnl + 1, myn - 50, 54, 49, 0);

    HgWSetFillColor(layer1, HG_RED);
    HgWBoxFill(layer1, mxnl - 55, myn + 1, 54, 49, 0);

    HgWSetFillColor(layer1, HG_GREEN);
    HgWBoxFill(layer1, mxnl + 1, myn + 1, 54, 49, 0);
}

// ipodの描画の関数
void ipod(double px, double py)
{
    HgWSetFillColor(layer1, HG_CYAN);
    HgWBoxFill(layer1, px, py, 54, 70, 1);

    HgWSetFillColor(layer1, HG_BLACK);
    HgWBoxFill(layer1, px + 7, py + 25, 40, 40, 1);

    HgWSetFillColor(layer1, HG_WHITE);
    HgWCircleFill(layer1, px + 27, py + 12, 10, 1);

    HgWSetFillColor(layer1, HG_CYAN);
    HgWCircleFill(layer1, px + 27, py + 12, 5, 1);
}

// ジョブズがりんご取った時の光った顔
void tentionupjobs(double jx)
{
    // 顔
    HgWCircle(layer1, jx, 70, 55);

    // 口
    HgWBox(layer1, jx - 20, 30, 44, 24);

    // 光った時の目ん玉右
    HgWSetFillColor(layer1, HG_YELLOW);
    HgWCircleFill(layer1, jx + 20, 80, 15, 0);
    // 黒目右
    HgWSetFillColor(layer1, HG_WHITE);
    HgWCircleFill(layer1, jx + 20, 80, 3, 1);

    // 光った時の目ん玉左
    HgWSetFillColor(layer1, HG_YELLOW);
    HgWCircleFill(layer1, jx - 20, 80, 15, 0);
    // 黒目左
    HgWSetFillColor(layer1, HG_WHITE);
    HgWCircleFill(layer1, jx - 20, 80, 3, 1);
}

// りんご以外のやつ取った時のジョブズの顔
void tentiondownjobs(double jx)
{
    // 顔
    HgWCircle(layer1, jx, 70, 55);

    // 口
    HgWLine(layer1, jx - 20, 30, jx + 20, 30);

    //目ん玉右
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, jx + 20, 80, 2, 1);

    //目ん玉左
    HgWSetFillColor(layer1, HG_BLACK);
    HgWCircleFill(layer1, jx - 20, 80, 2, 1);

    // 右目の線
    HgWLine(layer1, jx + 12, 80, jx + 28, 80);
    // 左目の線
    HgWLine(layer1, jx - 28, 80, jx - 12, 80);
}

// ジョブズの画像を持ってくる関数
void jobsimage(int lay, int img)
{
    HgWImageDrawRect(layer1, 700.0, 350.0, 400.0, 345.0, img, 240.0, 0.0, 400.0, 0.0 ); 
}

// ジョブズの画像を持ってくる関数
void geaituimage(int img2)
{
    HgImageDrawRect(700.0, 200.0, 350.0, 345.0, img2, 0.0, 0.0, 0.0, 0.0);
}

// マイクロソフト斜めも上に戻す