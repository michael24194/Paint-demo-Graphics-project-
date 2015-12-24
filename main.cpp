
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#define draw 1
#define paramet 2
#define mid 3
#define savel 4
#define loadl 5
#define savec 6
#define loadc 7
#define cart 9
#define polar 10
#define itpolar 11
#define polarE 12
#define cartE 13
std::vector <std::string> logB;
std::vector <std::string> logA;
int mode;
int ctr = 0;
std::vector <int> arr;
void drawFourPixels(HDC hdc,int xc,int yc,int x,int y,COLORREF color)
{
    //color = RGB(0,0,0);
    SetPixel(hdc,xc+x,yc+y,color);
    //color = RGB(200,0,0);
    SetPixel(hdc,xc-x,yc+y,color);
    //color = RGB(0,0,170);
    SetPixel(hdc,xc+x,yc-y,color);
    //color = RGB(0,0,0);
    SetPixel(hdc,xc-x,yc-y,color);
    //  = RGB(155,0,155);
    ///parametricLine(hdc,xc+x,yc+y,xc-x,yc-y,RGB(175,175,175));
    ///parametricLine(hdc,xc+y,yc+x,xc-y,yc-x,RGB(175,175,175));
    ///parametricLine(hdc,xc+x,yc-y,xc-x,yc+y,RGB(0,0,50));
    ///parametricLine(hdc,xc-y,yc+x,xc+y,yc-x,RGB(0,0,50));
}
void drawEightPixels(HDC hdc,int xc,int yc,int x,int y,COLORREF color)
{
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc-x,yc-y,color);
    SetPixel(hdc,xc+y,yc+x,color);
    SetPixel(hdc,xc+y,yc-x,color);
    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc-y,yc-x,color);
}
void polarEllipse(HDC hdc,int xc,int yc,int x1,int y1,int x2,int y2)
{
    double a = sqrt(((xc-x1)*(xc-x1)) + ((yc-y1)*(yc-y1)));
    double b = sqrt(((x2-xc)*(x2-xc)) + ((y2-yc)*(y2-yc)));
    //drawFourPixels(hdc,xc,yc,a,b,RGB(255,255,255));
    double theta = 0;
    double dtheta = 1.0 / std::max(a,b);
    double x = a;
    double y = 0;
    while (x > 0)
    {
        theta += dtheta;
        x = a * cos(theta);
        y = b * sin(theta);
        drawFourPixels(hdc,xc,yc,x,y,RGB(255,255,255));
    }
}
void cartEllipse(HDC hdc,int xc,int yc,int x1,int y1,int x2,int y2)
{
    double a = sqrt(((xc-x1)*(xc-x1)) + ((yc-y1)*(yc-y1)));
    double b = sqrt(((x2-xc)*(x2-xc)) + ((y2-yc)*(y2-yc)));
    //drawFourPixels(hdc,xc,yc,a,b,RGB(255,255,255));
    double x = 0;
    double y = b;
    while (x * b*b <= y * a*a)
    {
        x++;
        y = b * sqrt( 1 - ((x*x) / (a*a)) );
        drawFourPixels(hdc,xc,yc,x,y,RGB(200,55,25));
    }
    x = a;
    y = 0;
    while (x * b*b >= y * a*a)
    {
        y++;
        x = a * sqrt( 1 - ((y*y) / (b*b)) );
        drawFourPixels(hdc,xc,yc,x,y,RGB(200,55,25));
    }
}



void cartCir(HDC hdc,int xc,int yc,int x,int y)
{
    COLORREF color = RGB(200,0,0);
    double R = sqrt(((xc-x)*(xc-x)) + ((yc-y)*(yc-y)));
    x = 0;
    y = R;
    drawEightPixels(hdc,xc,yc,x,y,color);
    while (x < y)
    {
        x++;
        y = sqrt(R*R - x*x);
        drawEightPixels(hdc,xc,yc,x,y,color);
    }
}
void polarCir(HDC hdc,int xc,int yc,int x,int y)
{
    COLORREF color = RGB(0,0,0);
    double R = sqrt(((xc-x)*(xc-x)) + ((yc-y)*(yc-y)));
    x = R;
    y = 0;
    drawEightPixels(hdc,xc,yc,x,y,color);
    double theta = 0;
    double dtheta = 1.0 / R;
    while (x > y)
    {
        theta += dtheta;
        x = R * cos(theta);
        y = R * sin(theta);
        drawEightPixels(hdc,xc,yc,x,y,color);
    }

}
void iterativePolarCir(HDC hdc,int xc,int yc,int x,int y)
{
    COLORREF color = RGB(0,0,210);
    double R = sqrt(((xc-x)*(xc-x)) + ((yc-y)*(yc-y)));
    x = R;
    y = 0;
    double dtheta = 1.0 / R;
    drawEightPixels(hdc,xc,yc,x,y,color);
    double ct = cos(dtheta);
    double st = sin(dtheta);
    double x1 = R;
    double y1 = 0;
    while (x1 > y1)
    {
        x1 = (x1*ct)-(y1*st);
        y1 = (x1*st)+(y1*ct);
        drawEightPixels(hdc,xc,yc,x1,y1,color);
    }

}
void wovL(int mode,int x1,int y1,int x2,int y2)
{
    if (mode == 1)
    {
        logA.push_back("DDA");
    }
    else if (mode == 2)
    {
        logA.push_back("parametric");
    }
    else if (mode == 3)
    {
        logA.push_back("mid");
    }
    std::stringstream a;
    std::string t;
    a << x1;
    a >> t;
    logA.push_back(t);
    std::stringstream a1;
    std::string t1;
    a1 << y1;
    a1 >> t1;
    logA.push_back(t1);
    std::stringstream a2;
    std::string t2;
    a2 << x2;
    a2 >> t2;
    logA.push_back(t2);
    std::stringstream a3;
    std::string t3;
    a3 << y2;
    a3 >> t3;
    logA.push_back(t3);
}

void wovC(int mode,int x1,int y1,int x2,int y2)
{
    if (mode == 4)
    {
        logB.push_back("cart");
    }
    else if (mode == 5)
    {
        logB.push_back("polar");
    }
    else if (mode == 6)
    {
        logB.push_back("itpolar");
    }
    std::stringstream a;
    std::string t;
    a << x1;
    a >> t;
    logB.push_back(t);
    std::stringstream a1;
    std::string t1;
    a1 << y1;
    a1 >> t1;
    logB.push_back(t1);
    std::stringstream a2;
    std::string t2;
    a2 << x2;
    a2 >> t2;
    logB.push_back(t2);
    std::stringstream a3;
    std::string t3;
    a3 << y2;
    a3 >> t3;
    logB.push_back(t3);
}

void parametricLine(HDC hdc,int x1,int y1,int x2,int y2)
{
    COLORREF color = RGB(255,0,0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    float max;
    if (dy > dx)
        max = dy;
    else
        max = dx;
    double alp = 0.0001;
    for(double i=0.0; i<1; i+=alp)
    {
        int x = x1 + i*dx;
        int y = y1 + i*dy;
        SetPixel(hdc,round(x),round(y),color);
        // std::cout << x << " " << y << " " << alp << "\n";
    }
}
void drawline(HDC hdc,int xs,int ys,int xe,int ye)
{
    COLORREF color=RGB(0,0,0);
    //SetPixel(hdc,xs,ys,color);
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;// as line may be increasing or decreasing
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),color);
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,color);
        }
    }
}
void midPoint(HDC hdc,const int xs,const int ys,const int xe,const int ye )
{
    COLORREF color=RGB(155,0,155);

    int x1=xs;
    int y1=ys;

    int x2=xe;
    int y2=ye;

    if(xs>xe)
    {
        x1=xe;
        y1=ye;

        x2=xs;
        y2=ys;
    }

    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int inc_dec=((y2>=y1)?1:-1);

    if(dx>dy)
    {
        int chang2=(2*dy);
        int chang1=(2*(dy-dx));
        int dInitial=((2*dy)-dx);

        int x=x1;
        int y=y1;

        SetPixel(hdc,(int)x ,(int)y,color);

        while(x<x2)
        {
            x++;

            if(dInitial<0)
                dInitial+=chang2;

            else
            {
                y+=inc_dec;
                dInitial+=chang1;
            }

            SetPixel(hdc,(int)x ,(int)y,color);
        }
    }

    else
    {
        int two_dx=(2*dx);
        int two_dx_dy=(2*(dx-dy));
        int dInitial=((2*dx)-dy);

        int x=x1;
        int y=y1;

        SetPixel(hdc,(int)x ,(int)y,color);

        while(y!=y2)
        {
            y+=inc_dec;

            if(dInitial<0)
                dInitial+=two_dx;

            else
            {
                x++;
                dInitial+=two_dx_dy;
            }

            SetPixel(hdc,(int)x ,(int)y,color);
        }
    }

}
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               "Assignment 1",       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;
    hdc=GetDC(hwnd);
    int temp;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        HMENU hMenubar = CreateMenu();
        HMENU opt = CreateMenu();

        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)opt, "File");

        AppendMenu(opt, MF_STRING, savel, "Save Line");
        AppendMenu(opt, MF_STRING, loadl, "Load Line");
        AppendMenu(opt, MF_STRING, savec, "Save Circle");
        AppendMenu(opt, MF_STRING, loadc, "Load Circle");

        HMENU line = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)line, "Line");

        AppendMenu(line, MF_STRING, draw, "DDA");
        AppendMenu(line, MF_STRING, paramet, "Parametric");
        AppendMenu(line, MF_STRING, mid, "Midpoint");

        HMENU circle = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)circle, "Circle");

        AppendMenu(circle, MF_STRING, polar, "Polar");
        AppendMenu(circle, MF_STRING, cart, "Cartesian");
        AppendMenu(circle, MF_STRING, itpolar, "Iterative polar");

        HMENU ellipse = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)ellipse, "Ellipse");

        AppendMenu(ellipse, MF_STRING, polarE, "Polar");
        AppendMenu(ellipse, MF_STRING, cartE, "Cartesian");

        SetMenu(hwnd, hMenubar);
        break;
    }
    case WM_COMMAND:
    {
        if(LOWORD(wParam) == draw)
        {
            mode = 1;
            std::cout << "DDA Line\n";
        }
        else if (LOWORD(wParam) == paramet)
        {
            mode = 2;
            std::cout << "Parametric Line\n";
        }
        else if (LOWORD(wParam) == mid)
        {
            mode = 3;
            std::cout << "Midpoint Line\n";
        }
        else if (LOWORD(wParam) == cart)
        {
            mode = 4;
            std::cout << "Cartesian Circle\n";
        }
        else if (LOWORD(wParam) == polar)
        {
            mode = 5;
            std::cout << "Polar Circle\n";
        }
        else if (LOWORD(wParam) == itpolar)
        {
            mode = 6;
            std::cout << "Iterative polar Circle\n";
        }
        else if (LOWORD(wParam) == polarE)
        {
            mode = 7;
            std::cout << "Polar Ellipse\n";
        }
        else if (LOWORD(wParam) == cartE)
        {
            mode = 8;
            std::cout << "Cartesian Ellipse\n";
        }
        else if (LOWORD(wParam) == savel)
        {
            std::ofstream f;
            f.open("logLine.txt");
            for (int i=0;i<logA.size();i++)
            {
                f << logA[i] << "\n";
            }
            std::cout << "Lines are saved!\n";
            f.close();
        }
        else if (LOWORD(wParam) == loadl)
        {
            std::ifstream f;
            f.open("logLine.txt");
            while(!f.eof())
            {
                std::string lineType;
                std::string STx1;
                std::string STy1;
                std::string STx2;
                std::string STy2;
                std::stringstream a0;
                std::stringstream a1;
                std::stringstream a2;
                std::stringstream a3;
                int x1;
                int y1;
                int x2;
                int y2;
                f >> lineType;
                if (lineType == "parametric")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    parametricLine(hdc,x1,y1,x2,y2);
                }
                else if (lineType == "DDA")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    drawline(hdc,x1,y1,x2,y2);
                }
                else if (lineType == "mid")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    midPoint(hdc,x1,y1,x2,y2);
                }
            }
            std::cout << "Saved Lines are loaded!\n";
            f.close();
        }
        else if (LOWORD(wParam) == savec)
        {
            std::ofstream f;
            f.open("logCircle.txt");
            for (int i=0;i<logB.size();i++)
            {
                f << logB[i] << "\n";
            }
            std::cout << "Circles are saved!\n";
            f.close();
        }
        else if (LOWORD(wParam) == loadc)
        {
            std::ifstream f;
            f.open("logCircle.txt");
            while(!f.eof())
            {
                std::string circleType;
                std::string STx1;
                std::string STy1;
                std::string STx2;
                std::string STy2;
                std::stringstream a0;
                std::stringstream a1;
                std::stringstream a2;
                std::stringstream a3;
                int x1;
                int y1;
                int x2;
                int y2;
                f >> circleType;
                if (circleType == "cart")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    cartCir(hdc,x1,y1,x2,y2);
                }
                else if (circleType == "polar")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    polarCir(hdc,x1,y1,x2,y2);
                }
                else if (circleType == "itpolar")
                {
                    f >> STx1;
                    f >> STy1;
                    f >> STx2;
                    f >> STy2;
                    a0 << STx1;
                    a0 >> x1;
                    a1 << STy1;
                    a1 >> y1;
                    a2 << STx2;
                    a2 >> x2;
                    a3 << STy2;
                    a3 >> y2;
                    polarCir(hdc,x1,y1,x2,y2);
                }
            }
            std::cout << "Saved Circles are loaded!\n";
            f.close();
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (ctr == 0)
        {
            arr.push_back(GET_X_LPARAM(lParam));
            arr.push_back(GET_Y_LPARAM(lParam));
            std::cout <<"X1 : " << arr[0] << " Y1 : " << arr[1] << "\n";
            ctr = 1;
            break;
        }
        else if (ctr == 1)
        {
            arr.push_back(GET_X_LPARAM(lParam));
            arr.push_back(GET_Y_LPARAM(lParam));
            std::cout <<"X2 : " << arr[2] << " Y2 : " << arr[3] << "\n";
            ctr = 3;
            if (mode == 7 || mode == 8)
            {
                ctr = 2;
                break;
            }
        }
        else if (ctr == 2)
        {
            arr.push_back(GET_X_LPARAM(lParam));
            arr.push_back(GET_Y_LPARAM(lParam));
            std::cout <<"X3 : " << arr[4] << " Y3 : " << arr[5] << "\n";
            ctr = 3;
        }
        if (arr[0] > arr[2] && (mode == 1 || mode == 2 || mode == 3))
        {
            std::cout << "I Entered the condition\n";
            std::swap(arr[0],arr[2]);
            std::swap(arr[1],arr[3]);
        }
        if (mode == 1)
        {
            drawline(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovL(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 2)
        {
            parametricLine(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovL(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 3)
        {
            midPoint(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovL(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 4)
        {
            cartCir(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovC(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 5)
        {
            polarCir(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovC(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 6)
        {
            iterativePolarCir(hdc,arr[0],arr[1],arr[2],arr[3]);
            wovC(mode,arr[0],arr[1],arr[2],arr[3]);
        }
        else if (mode == 7)
        {
            polarEllipse(hdc,arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
        }
        else if (mode == 8)
        {
            cartEllipse(hdc,arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
        }
        ctr = 0;
        arr.clear();
        ReleaseDC(hwnd,hdc);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
        return 0;
    }


}
