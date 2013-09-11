#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sys/time.h>

#define MAX 1000000

using namespace std;

typedef struct statistics {
	long compare_count;   //关键字的比较次数
	long move_count;      //关键字的移动次数（其中关键字交换计为3次移动）
}STAT;

void print_array(long R[],long n)
{
	for(int i=1;i<=n;i++)
		cout<<setw(4)<<R[i]<<' ';
	cout<<endl;
}

//------------------------------------------------------------------------------
//插入排序
//------------------------------------------------------------------------------
static STAT insertsort_stat;
void InsertSort(long R[], long n)
{
	long y=1;
	long j;
	for(long i=2;i<=n;++i)
	{
		insertsort_stat.compare_count++;
		if(R[i]<R[i-1])
		{
			R[0]=R[i];//复制为哨兵
			insertsort_stat.move_count++;
			for( j=i-1;R[0]<R[j];--j)
			{
				insertsort_stat.compare_count++;
				R[j+1]=R[j];//记录后移
				insertsort_stat.move_count++;
			}
			R[j+1]=R[0];//插入到正确位置
			insertsort_stat.move_count++;
		}
		/*
		cout<<"第"<<y<<"趟:"<<' ';
		y++;
		cout<<setw(4)<<"["<<R[1];
		for(long x=2;x<=i;x++)
			cout<<setw(4)<<R[x];
		cout<<"]";
		for(long x=i+1;x<=n;x++)
			cout<<setw(4)<<R[x];
		cout<<endl;
		*/
	}
}

//------------------------------------------------------------------------------
//希尔排序
//------------------------------------------------------------------------------
static STAT shellsort_stat;
void ShellInsert(long arr[],int n,int dk)      //n为元素个数，dk为增量
{
	for(int i=dk+1;i<=n;i++)       //当dk==1时为直接插入排序，希尔排序可以减少直接插入排序的比较和移动次数
	{
		shellsort_stat.compare_count++;
		if(arr[i]<arr[i-dk])
		{
			arr[0]=arr[i];        //设置监视哨
			shellsort_stat.move_count++;
			int j;
			for(j=i-dk;j>0&&arr[0]<arr[j];j-=dk) {    //注意这里要确保j>0
				shellsort_stat.compare_count++;
				arr[j+dk]=arr[j];
				shellsort_stat.move_count++;
			}
			arr[j+dk]=arr[0];
			shellsort_stat.move_count++;
		}
	}
}

void ShellSort(long arr[],int n)      //希尔排序可形象比喻为：先进行大范围调节在进行小范围调节
{
	int dk=n/2;
	for(;dk>=1;dk/=2)    //依次减小增量,当增量较少为1时进行直接插入排序（小调节）
		ShellInsert(arr,n,dk);       //希尔插入
}

//------------------------------------------------------------------------------
//冒泡排序
//------------------------------------------------------------------------------
static STAT bubblesort_stat;
void BubbleSort(long R[], long n)
{	
	long y=1;
	long i;
	i = n;
	while(i>1)
	{
		long lastExchangeIndex=1;//表示已经有序
		for(long j=1;j<i;j++) {
			bubblesort_stat.compare_count++;
			if(R[j+1]<R[j])
			{
				long t=R[j];
				R[j]=R[j+1];
				R[j+1]=t;
				bubblesort_stat.move_count += 3;
				lastExchangeIndex=j;//记下进行的位置
			}
		}
		i=lastExchangeIndex;//本趟进行过交换的最后一个记录的位置
		/*
		cout<<"第"<<y<<"趟:";
		y++;
		for(long x=1;x<=i;x++)		
			cout<<setw(4)<<R[x];
		cout<<setw(3)<<"["<<R[i+1];
		for(long x=i+2;x<=n;x++)
			cout<<setw(4)<<R[x];
		cout<<"]";
		cout<<endl;
		*/
	}
}
//------------------------------------------------------------------------------
//选择排序
//------------------------------------------------------------------------------
static STAT selectsort_stat;
long SelectMinKey(long R[],long i,long n)//在 R[i..R.length] 中选择关键字最小的记录
{
	long temp=i;//记录最小的元素值的位置
	for(int j=i;j<=n;j++)
	{
		selectsort_stat.compare_count++;
		if(R[temp]>R[j])
			temp=j;
	}
	return temp;
}

void SelectSort(long R[],long n)
{
	long j,i,t;
	long y=1;
	for( i=1;i<n;i++)
	{
		j = SelectMinKey(R,i,n);// 在 R[i..L.length] 中选择关键字最小的记录
		if (i!=j) // 与第 i 个记录交换
		{
			t=R[i];
			R[i]=R[j];
			R[j]=t;
			selectsort_stat.move_count+=3;
		}
		/*
		cout<<"第"<<y<<"趟:"<<' ';
		y++;
		for(long x=1;x<=i;x++)
			cout<<setw(4)<<R[x];
		cout<<setw(3)<<"["<<R[i+1];
		for(long x=i+2;x<=n;x++)
			cout<<setw(4)<<R[x];
		cout<<"]";
		//print(R,n);
		cout<<endl;
		*/
	}
}

//------------------------------------------------------------------------------
//	快速排序
//------------------------------------------------------------------------------
static STAT quicksort_stat;
int Partition (long R[], long low, long high,long n)
{
	R[0] =R[low]; 
	long pivotkey = R[low];  // 枢轴 
	quicksort_stat.move_count += 2;
	while (low<high) 
	{
		quicksort_stat.compare_count++;
		while(low<high&& R[high]>=pivotkey) {// 从右向左搜索
			-- high;
			quicksort_stat.compare_count++;
		}
		R[low] = R[high];
		quicksort_stat.move_count++;
		while (low<high && R[low]<=pivotkey) {// 从左向右搜索
			++ low;
			quicksort_stat.compare_count++;
		}
		R[high] = R[low];
		quicksort_stat.move_count++;
	}
	
	R[low] =R[0]; 
	quicksort_stat.move_count++;

	return low;
}// Partition

void QuickSort (long R[], int low, int high, long n, long y)// 对记录序列L.r[low..high]进行快速排序
{

	if (low < high) // 长度大于1
	{        

		long pivotloc = Partition(R,low,high,n);// 对 L.r[low..high] 进行一次划分
		quicksort_stat.move_count++;
		/*
		cout<<"第"<<y<<"趟:";
		y++;
		print_array(R,pivotloc-1);
		cout<<setw(2)<<"["<<R[pivotloc];
		cout<<"]";
		for(long x=pivotloc+1;x<=n;x++)
			cout<<setw(5)<<R[x];
		cout<<endl;
		*/
		QuickSort(R, low, pivotloc-1,n,y);   // 对低子序列递归排序
		QuickSort(R, pivotloc+1, high,n,y); // 对高子序列递归排序

	}
} 
// QSort
void qsort(long R[],long n)
{
	long y=1;
	QuickSort(R,1,n,n,y);
}
//------------------------------------------------------------------------------
//操作选择函数
//------------------------------------------------------------------------------
void operate(long a[], long n)
{
	long *R = new long [n];
	struct timeval tv_begin, tv_end;
	long Time;//排序时间
	char ch;
	cout << "请选择排序算法：";
	cin >> ch;
	switch(ch){
		case '1':
		{
			cout<<endl;
			cout<<"您选择的是插入排序"<<endl;
			for(int i=1; i<=n; i ++)
			{
				R[i] = a[i];
			}
			gettimeofday(&tv_begin, NULL);
			InsertSort(R, n);
			gettimeofday(&tv_end, NULL);
			Time = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
			print_array(R,n);
			cout << endl;
			cout << "插入排序所用时间：  " << Time << "us\n";
			cout << "插入排序比较次数：  " << insertsort_stat.compare_count << endl;
			cout << "插入排序交换次数：  " << insertsort_stat.move_count << endl;
			cout << endl;
			insertsort_stat.compare_count = 0;
			insertsort_stat.move_count = 0;
			operate(a, n);
			break;
		}

		case '2':
		{
			cout<<endl;
			cout<<"您选择的是希尔排序"<<endl;
			for(int i=1; i<=n; i ++)
			{
				R[i] = a[i];
			}
			gettimeofday(&tv_begin, NULL);
			ShellSort(R, n);
			gettimeofday(&tv_end, NULL);
			Time = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
			print_array(R,n);
			cout << endl;
			cout << "希尔排序所用时间：  " << Time << "us\n";
			cout << "希尔排序比较次数：  " << shellsort_stat.compare_count << endl;
			cout << "希尔排序交换次数：  " << shellsort_stat.move_count << endl;
			cout << endl;
			shellsort_stat.compare_count = 0;
			shellsort_stat.move_count = 0;
			operate(a, n);
			break;
		}

		case '3':
		{
			cout<<endl;
			cout<<"您选择的是冒泡排序"<<endl;
			for(int i = 1; i <= n; i++)//将随机数付给R[i]
			{
				R[i] = a[i];
			}
			gettimeofday(&tv_begin, NULL);
			BubbleSort(R, n);
			gettimeofday(&tv_end, NULL);
			Time = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
			print_array(R,n);
			cout << endl;
			cout << "冒泡排序所用时间：  " << Time << "us\n";
			cout << "冒泡排序比较次数：  " << bubblesort_stat.compare_count << endl;
			cout << "冒泡排序交换次数：  " << bubblesort_stat.move_count << endl;
			cout<<endl;
			bubblesort_stat.compare_count = 0;
			bubblesort_stat.move_count = 0;
			operate(a, n);
			break;
		}


		case '4':
		{
			cout<<endl;
			cout<<"您选择的是快速排序"<<endl;
			for(int i=1; i<=n; i ++)
			{
				R[i] = a[i];
			}
			gettimeofday(&tv_begin, NULL);
			qsort(R, n);
			gettimeofday(&tv_end, NULL);
			Time = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
			print_array(R, n);
			cout<<endl;
			cout << "快速排序所用时间：  " << Time << "us\n";
			cout << "快速排序比较次数：  " << quicksort_stat.compare_count << endl;
			cout << "快速排序交换次数：  " << quicksort_stat.move_count << endl;
			cout << endl;
			quicksort_stat.compare_count = 0;
			quicksort_stat.move_count = 0;
			operate(a, n);
			break;
		}

		case '5':
		{
			cout<<endl;
			cout<<"您选择的是简单选择排序"<<endl;
			for(int i = 1; i <= n; i ++)
			{
				R[i] = a[i];
			}
			gettimeofday(&tv_begin, NULL);
			SelectSort(R, n);
			gettimeofday(&tv_end, NULL);
			Time = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
			print_array(R,n);
			cout << endl;
			cout << "简单选择排序所用时间：  " << Time << "us\n";
			cout << "简单选择排序比较次数：  " << selectsort_stat.compare_count << endl;
			cout << "简单选择排序交换次数：  " << selectsort_stat.move_count << endl;
			cout << endl;
			selectsort_stat.compare_count = 0;
			selectsort_stat.move_count = 0;
			operate(a, n);
			break;
		}

		default:
		{
			cout << "输入错误，请选择正确的操作！" << endl;
			operate(a, n);
			break;
		}

		case '0':
		{
			cout<<"程序已退出"<<endl;
			break;
		}
	}

}

//------------------------------------------------------------------------------
//导航菜单函数
//------------------------------------------------------------------------------
void DaoHang()
{
	cout<<"\n排序算法比较"<<endl;
	cout<<"------------"<<endl;
	cout<<"1 --- 插入排序"<<endl;
	cout<<"2 --- 希尔排序"<<endl;
	cout<<"3 --- 冒泡排序"<<endl;
	cout<<"4 --- 快速排序"<<endl;
	cout<<"5 --- 简单选择排序"<<endl;
	cout<<"0 --- 退出程序"<<endl;
	cout<<"------------"<<endl;
}
//--------------------------------------------------------------------------------
//随机输入函数
//--------------------------------------------------------------------------------
void Rand()
{
	cout << "\n请输入要产生的随机数的个数（0 <= n <= "<< MAX <<"）："<<endl;
	long int n;
	cin >> n;
	cout << endl;
	long *a = new long [n+1];
	srand((unsigned long)time(NULL));//产生一个以当前时间开始的随机种子
	for (long i=1; i<=n; i++)
		a[i] = rand() % (n * 10);//n为最大值,其随机域为0~n-1
	
	DaoHang();
	print_array(a,n);
	operate(a, n);
}
//--------------------------------------------------------------------------------
//手动输入函数
//--------------------------------------------------------------------------------
void HandInput()
{
	cout << "请输入数据个数："<< endl;
	int n;
	cout << "n = ";
	cin >> n;
	cout << endl;
	cout << "请输入" << n << "个数据：" <<endl;
	long *a = new long [n+1];
	for (long i=1; i<=n; i++)
		cin>>a[i];
	
	DaoHang();
	operate(a, n);
}

int main()
{
loop:
	cout<<"1:输入数据"<<endl<<"2:随机生成数据"<<endl;
	int x;
	cin>>x;
	switch(x) {
		case 2: {
			Rand();
			break;
		}
		case 1: {
			HandInput();
			break;
		}
		default:
			cout<<"输入错误,请重新输入!"<<endl;
			goto loop;
	}

	return 0;
}