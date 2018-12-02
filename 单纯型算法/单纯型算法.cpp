#include <iostream>
#include <string>
#include <cstring>
#include <set>
#include <algorithm>
#include <E:\�о���\�˳�ѧ\�������㷨\Fraction.h> 
using namespace std;

const long long SIZE = 100;

/*
	����ʵ�����Թ滮��׼���µĵ������㷨�� 
*/

class Simplex{
	private:
		int m;												//Լ���������� 
		int n;						   		   			   //�������� 
		Fraction A[SIZE][SIZE];				  			  //Լ��ϵ������ 
		Fraction b[SIZE];					 			 //���������
		Fraction c[SIZE]; 								//Ŀ�꺯��ϵ��
		Fraction cb[SIZE];							   //��������Ӧ��Ŀ��ϵ�� 
		Fraction theta[SIZE];			 			 //�������뻻��Լ������������������Ľ��
		int basic_vector_list[SIZE];					//�����б� 
	public:
		//��ʼ�����Թ滮Ŀ�꺯����Լ������ 
		void Init(){
			//���ȳ�ʼ�����ϵ������
			Fraction tmp;
			tmp.set("0/1");
			for(int i = 0 ; i < SIZE ; i++){
				for(int j = 0 ; j < SIZE ; j++){
					this->A[i][j] = tmp;
				}
				this->b[i] = this->c[i] = tmp;
			}
			int m,n,type,direction;
			cout<<"------------�������㷨����------------------------"<<endl; 
			cout<<"������Լ����������m:"<<endl;
			cin>>m;
			this->m = m;
			cout<<"�������������n:"<<endl;
			cin>>n;
			this->n = n;
			cout<<"������Լ������ϵ���벻��ʽ����(-1����<=��0����=��1����>=)"<<endl;
			for(int i = 1 ; i <= n ; i++){
				cout<<"\t\tx"<<i; 
			}
			cout<<"\t\t"<<"����ʽ����\t\t������"<<endl;
			int cnt = 0;	//�ɳڱ��������� 
			for(int i = 0 ; i < m ; i++){
				cout<<"���벻��ʽ"<<i+1<<":";
				Fraction a;
				for(int j = 0 ; j < n ; j++){
					string str;
					cin>>str;
					a.set(str);
					this->A[i][j] = a;
				}
				//���벻��ʽ����ͳ����� 
				string _b;		//������ 
				cin>>direction>>_b;
				if(direction == -1){			//����ʽ����Ϊ<=,Լ�������Ӧ�м�һ���ɳڱ��� 
					Fraction relaxation_variable;
					relaxation_variable.set("1/1");
					this->A[i][n+cnt] = relaxation_variable;
					cnt++;
				}else if(direction == 1){			//����ʽ����Ϊ>=,Լ�������Ӧ�м�ȥһ���ɳڱ��� 
					Fraction relaxation_variable;
					relaxation_variable.set("-1/1");
					this->A[i][n+cnt] = relaxation_variable;
					cnt++;
				}
				Fraction b_;
				b_.set(_b);
				this->b[i] = b_;
			} 
			cout<<"������Ŀ�꺯���Ż����ͺ�Ŀ�꺯��ϵ������(����ֵΪ1�������,-1������С)"<<endl; 
			cout<<"������Ŀ�꺯���Ż����ͣ�"<<endl; 
			cin>>type;
			cout<<"������Ŀ�꺯��ϵ����"<<endl;
			for(int i = 1 ; i <= n ; i++){
				cout<<"\tx"<<i;
			}
			cout<<endl;
			for(int i = 0 ; i < this->n ; i++){
				Fraction c_;
				c_.set("0/1");
				this->c[i] = c_;
				this->cb[i] = c_;
			}
			for(int i = 0 ; i < n ; i++){
				string str;
				cin>>str;
				if(type == -1){				// ��Ŀ�꺯��������Сֵʱ��Ҫ����ģ��ת����ת��Ϊ���ֵ 
					if(str[0] == '-'){		//str1Ϊ����ʱ����ȥ������ 
						str = str.erase(0,1);
					}else if(str[0] != '0'){  //str1Ϊ����ʱ�����Ϸ��� 
						str = "-"+str;
					}
				}
				Fraction C;
				C.set(str);
				this->c[i] = C;
				this->basic_vector_list[i] = i; 
			}
			//���µ�ǰ�ı������� 
			this->n += cnt; 
			//���в��Ⱥų��֣���Ҫ�����ɳڱ�������ӦĿ��Լ��ϵ����Ϊ0 
			for(int i = n ; i < this->n ; i++){
				Fraction c_;
				c_.set("0/1");
				this->c[i] = c_;
				this->cb[i] = c_;
 				this->basic_vector_list[i] = i; 
			}
		}
		
		//���Թ滮��׼�͵������㷨�ⷨ
		bool SimplexSolve(){
			bool ans; 
			//���Ƚ�Լ��ϵ������ֽ�ɻ�����ͷǻ�����֮���ҳ���Ӧ�Ŀ��л���ǿ��л� 
			//�����������Ĭ�ϱ任�ɵ�λ���Է��㵥�����㷨����ؾ������
			//���ȳ�ʼ���Ƿ�Ϊ��λ�����ı�־�����Ԫ��1���±����� 
			//flag[i]�Ǽ�¼��i���Ƿ�Ϊ��λ����,index[i]��¼��i����Ϊ��λ����ʱ1���±� 
			int flag[this->n],index[this->n];
			//�ж��Ƿ����m�������޹ص�λ����
			int cnt_unit_vector = this->exsitUnitMatrix(flag,index,this->n);
			if(cnt_unit_vector != this->m){	//δ�ҵ�m�������޹ص�λ���� 
				Transform(flag,index,this->n);
			} 
			//��ʼ����ʽ���� 
			Fraction test_array[this->n];
			for(int i = 0 ; i < this->n ; i++){
				Fraction a;
				a.set("0/1");
				test_array[i] = a;
			}
			this->Print();
			while(1){
				//�������������(��ʽ)
				this->ComputeTestNumber(test_array,this->n);
				cout<<endl<<"������Ϊ��"<<endl;
				for(int i = 0 ; i < this->n ; i++){
					cout<<test_array[i].result()<<" ";
				}
				cout<<endl;
				//�жϵ�ʽ�Ƿ�ȫС��0
				//cout<<"�Ƿ�ȫ��С�ڵ���0��"<<this->isAllLessZero(test_array,this->n)<<endl;
				if(this->isAllLessZero(test_array,this->n)){
					ans = true;
					break;
				}else{
					//������������Ķ�Ӧ�ı������±�(���±�)������Ӧ�ı�����Ϊ��������� 
					int max_col = this->Find_Max_TestNumber(test_array,this->n);
					cout<<"��Ҫ�������:"<<max_col+1<<endl;
					//��ö�Ӧ��Լ������������
					Fraction p_index[this->m];
					for(int i = 0 ; i < m ;i++){
						p_index[i] = this->A[i][max_col]; 
					}
					//�ж϶�ӦԼ�������������Ƿ�ȫС��0
					if(this->isAllLessZero(p_index,this->m)){//ȫС��0,û�����Ž� 
						ans = false;
						break;
					}else{//��ȫС��0��ѡ����С�ı�����Ϊ��������
						//���Ƚ��н�Լ�������������ͳ������������õ���Ӧ���
						this->Divide_Array(p_index,this->m);
						//cout<<endl<<"------"<<endl;
						/*for(int i = 0 ; i < this->m ; i++){
							cout<<p_index[i].result()<<" "; 
						}
						cout<<endl<<"------"<<endl;*/
						//�����������Ѿ�����˹��Ԫ��ת��Ϊ��˵�λ������˼��˾�������
						//Ѱ��theta��������0�ķ�������С�ķ��� (���±�)
						int r = this->Find_Min_x(this->theta,this->m);
						/*cout<<endl<<"*********"<<endl;
						for(int i = 0 ; i < this->m ; i++){
							cout<<this->theta[i].result()<<" "; 
						}
						cout<<endl<<"*********"<<endl;*/
						int index = this->Find_BasicVector_Index(this->basic_vector_list[r]);
						cout<<"��Ҫ��������:"<<this->basic_vector_list[r]+1<<endl;
						//��ʼ��A[r][max_index]��λ��Ԫ��������Ԫ��A[r][max_index]ת��Ϊ1��
						//���������ȫ��ת��Ϊ0��������;�������Ԫ��������Ӧ�仯��
						this->transform(r,max_col);
						//���Ļ������б�
						//int index = this->Find_BasicVector_Index(r);
						this->basic_vector_list[index] = max_col;
						//���»�������Ӧ��Ŀ��ϵ������
						this->cb[r] = this->c[max_col]; 
					} 
				}
				this->Print();
			}
			return ans;
		} 
		
		//�ж�Լ�������е�col���Ƿ�Ϊ��λ���� 
		int isUnitVector(int col){
			int cnt0 = 0; 			//��¼Ԫ��Ϊ0�ĸ��� 
			int index = -1;			//��¼Ԫ��Ϊ1���±� 
			Fraction one;
			one.set("1/1");
			for(int i = 0; i < this->m ; i++){
				//����Ԫ��1 
				if(this->A[i][col].Compare2Fraction(one) == 0){
					index = i;
				}
				//����Ԫ��0 
				if(this->A[i][col].Compare2Zero() == 0){
					cnt0++; 
				}
			}
			//���д���m-1��Ԫ��0��ʣ��һ��Ԫ��1������Ԫ��1���±� 
			if(cnt0 == this->m-1 && index != -1){
				return index;
			}else{//���򷵻�-1 
				return -1;
			}
		}
		
		//�ж��Ƿ����m�������޹ص�λ���� 
		int exsitUnitMatrix(int* flag,int* index,int n){
			int cnt_unit_vector = 0;		//�洢��λ�������� 
			int cnt = 0;
			for(int i = n-1 ; i >= 0 ; i--){
				//�жϵ�i���Ƿ�λ���� 
				int _index = this->isUnitVector(i); 
				if(_index == -1){	//���ǵ�λ���� 
					flag[i] = 0;
					index[i] = -1; 
				}else{	//�ǵ�λ�������洢Ԫ��Ϊ1���±����ǵ�λ�����ı�־ 
					flag[i] = 1;
					index[i] = _index;
					//���μ�¼������ 
					this->basic_vector_list[cnt++] = i; 
					cnt_unit_vector++;
				}
			}
			sort(basic_vector_list,basic_vector_list+this->m);
			return cnt_unit_vector;
		} 
		
		void Transform(int* flag,int* index,int n){
			set<int> s;
			//���Ѿ��ǵ�λ��������������1���±���뼯�� 
			for(int i = 0 ; i < n ; i++){
				if(flag[i] == 1){
					s.insert(index[i]); 
				}
			}
			int cnt = 0;
			//��ʼ����ÿ�У�������m�����޹ص�λ���� 
			for(int i = this->n-1; i >= 0 && s.size() != this->m; i--){
				if(flag[i] == 1){	//��i���ǵ�λ���� 
					this->basic_vector_list[cnt] = i;		//�Ѹ����������ѡ�������б���
					this->cb[cnt] = this->c[i];				//����Ӧ��Ŀ�꺯��ϵ�������������Ӧ��Ŀ��ϵ�����鵱��
					cnt++; 
					continue;
				}else{				//��i�в��ǵ�λ����
					for(int j = 0 ; j < this->m ; j++){
						if(s.find(j) != s.end()){  //�����к����±�j�����Ѿ�����Ԫ��1�ڵ�j��λ�õĵ�λ���� 
							continue;
						}else{//�����ڣ���ôA[j][i]Ϊ��Ԫ,�Ѹ��е���Ϊ��λ���� 
							this->transform(j,i);
							s.insert(j);
							this->basic_vector_list[cnt] = i;		//�Ѹ����������ѡ�������б���
							this->cb[cnt] = this->c[i];				//����Ӧ��Ŀ�꺯��ϵ�������������Ӧ��Ŀ��ϵ�����鵱��
							cnt++; 
							break;
						}
					}
				}
			} 
		} 
		
		//�������������ʽ�� 
		void ComputeTestNumber(Fraction* test_array,int n){
			for(int i = 0 ; i < this->n ; i++){
				test_array[i] = this->c[i];
				for(int j = 0 ; j < this->m ; j++){
					Fraction tmp;
					tmp = tmp.MUL(this->cb[j],this->A[j][i]);
					test_array[i] = test_array[i].SUB(test_array[i],tmp);
				}
			} 
		}
		
		//�����ж��������Ƿ�ȫΪ0�ĺ��� 
		int isAllLessZero(Fraction* array,int size){
			/*cout<<endl<<"=========="<<endl;
			for(int i = 0 ; i < size ; i++){
				cout<<array[i].Compare2Zero()<<" ";
			}
			cout<<endl<<"============="<<endl;*/
			int flag = 1;
			for(int i = 0 ; i < size ; i++){
				if(array[i].Compare2Zero() == 1){//����������0 
					flag = 0;
					break;
				}
			}
			return flag;
		}		
		
		//Ѱ�Ҽ������е����ֵ
		int Find_Max_TestNumber(Fraction* test_array,int size){
			int index = 0;
			Fraction max;
			max.set("0/1"); 
			for(int i = 0 ; i < size ; i++){
				if(test_array[i].Compare2Zero() <= 0){//������0�ļ��������� 
					continue;
				}else{//����������0ʱ
					int flag = test_array[i].Compare2Fraction(max);
					if(flag == 1){//��ǰ��������max�󣬸���max���±� 
						max = test_array[i];
						index = i;
					}
				}
				//cout<<"max="<<max.result()<<" index="<<index<<endl;
			}
			return index;		//�����±� 
		}
		
		//Ѱ�ҳ���С��ֵ��Ӧ���±� 
		int Find_Min_x(Fraction* theta,int size){
			int index = 0;
			Fraction min;
			min.set("9999999/1");			//����Ϊ�������� 
			//cout<<index;
			//cout<<"min="<<min.result()<<" index="<<index<<endl;
			for(int i = 0 ; i < size ; i++){
				if(theta[i].Compare2Zero() <= 0){//������0�ļ��������� 
					continue;
				}else{//����������0ʱ
					int flag = theta[i].Compare2Fraction(min);
					if(flag == -1){//��ǰ��������minС������min���±� 
						min = theta[i];
						index = i;
					}	
				}
				//cout<<"min="<<min.result()<<" index="<<index<<endl;	
			}
			return index;		//�����±� 
		} 
		
		//��ÿ���з�Ѱ��1���±� 
		int FindOne(int col){
			int cnt0 = 0; 
			int index = -1;
			Fraction one;
			one.set("1/1");
			for(int i = 0; i < this->m ; i++){
				//����Ԫ��1 
				if(this->A[i][col].Compare2Fraction(one) == 0){
					index = i;
				}
				//����Ԫ��0 
				if(this->A[i][col].Compare2Zero() == 0){
					cnt0++; 
				}
			}
			//���д���m-1��Ԫ��0��ʣ��һ��Ԫ��1������Ԫ��1���±� 
			if(cnt0 == this->m-1 && index != -1){
				return index;
			}else{//���򷵻�-1 
				return -1;
			}
		}
		
		//Ѱ�һ������б���k���ڵ��±� 
		int Find_BasicVector_Index(int k){
			for(int i = 0 ; i < this->m ; i++){
				if(this->basic_vector_list[i] == k){
					return i;
				}
			} 
		}	
				
		// ����Լ�������������볣��������Ľ�� 
		void Divide_Array(Fraction* pk,int size){
			for(int i = 0 ; i < size ; i++){
				//����Fraction�ж��ڳ���Ϊ0�Ľ������Ϊ��-32768/1��
				this->theta[i] = this->theta[i].DIV(this->b[i],pk[i]);
			}
		}
		
		//��A[row][col]��λ��Ԫ�󣬽���ת��Ϊ1����������Ϊת��Ϊ0�������������Լ����������Ӧ���� 
		void transform(int row,int col){
			//���ȴ���row��һ�е����� 
			//A[row][col]��Ϊϵ�� 
			Fraction rate = this->A[row][col];
			//����row���еĳ�����b��Լ������A 
			this->b[row] = this->b[row].DIV(this->b[row],rate); 
			for(int i = 0 ; i < this->n; i++){
				this->A[row][i] = this->A[row][i].DIV(this->A[row][i],rate);
			} 
			//����ʣ���Ԫ��
			for(int i = 0 ; i < this->m; i++){
				if(i == row){//��������Ԫ�������� 
					continue;
				}
				Fraction rate = this->A[i][col];
				int flag = rate.Compare2Zero();
				if(flag == 0){	//A[i][col]Ϊ0���������� 
					continue;
				}else{	//A[i][col]��Ϊ0��rate=A[i][col]
					Fraction tmp; 
					//�Ե�i�н����б任 
					for(int j = 0 ; j < this->n ; j++){
						tmp = tmp.MUL(this->A[row][j],rate);
						this->A[i][j] = this->A[i][j].SUB(this->A[i][j],tmp);
					}
					//�Գ�������б任 
					tmp = tmp.MUL(this->b[row],rate);
					this->b[i] = this->b[i].SUB(this->b[i],tmp);
				}
			} 
		}
		
		//��A[row][col]�����������Ǹ�Ԫ�� 
		int Search_Col(int row,int col){
			int index = -1;		//index�����洢Ѱ�ҵ�Ԫ�ص������꣬-1����û���ҵ� 
			//�����һ�п�ʼ����������ǰ�зŵ�����棬��ֹ֮���ν������� 
			for(int i = this->m-1 ; i > row ; i--){
				if(this->A[i][col].Compare2Zero() != 0){   //�ҵ���Ϊ0��Ԫ�� 
					index = i;
					break;
				}
			}
			return index;
		} 
		
		//��A[row][col]�����������Ǹ�Ԫ�� 
		int Search_Row(int row,int col){
			int index = -1;		//index�����洢Ѱ�ҵ�Ԫ�ص������꣬-1����û���ҵ� 
			//�����һ�п�ʼ����������ǰ�зŵ�����棬��ֹ֮���ν������� 
			for(int i = this->n-1 ; i > col ; i--){
				if(this->A[row][i].Compare2Zero() != 0){   //�ҵ���Ϊ0��Ԫ�� 
					index = i;
					break;
				}
			}
			return index;
		} 
		
		//���н��� 
		void Swap_Row(int row1,int row2){
			//���±�Ϊrow1��row2���н��� 
			for(int i = 0 ; i < this->n ; i++){
				Fraction tmp = this->A[row1][i];
				this->A[row1][i] = this->A[row2][i];
				this->A[row2][i] = tmp;
			}
			//�Գ����������ӦԪ�ؽ��е���
			Fraction tmp = this->b[row1];
			this->b[row1] = this->b[row2];
			this->b[row2] = tmp; 
		}
		
		//���н��� 
		void Swap_Col(int col1,int col2){
			for(int i = 0 ; i < this->m ; i++){
				Fraction tmp = this->A[i][col1];
				this->A[i][col1] = this->A[i][col2];
				this->A[i][col2] = tmp;
			}
			//��Ŀ��Ŀ��ϵ�����л��� 
			Fraction tmp = this->c[col1];
			this->c[col1] = this->c[col2];
			this->c[col2] = tmp;
			//�����б���
			int tmp1 = this->basic_vector_list[col1];
			this->basic_vector_list[col1] = this->basic_vector_list[col2];
			this->basic_vector_list[col2] = tmp1; 
		}
		
		//�������Ž� 
		Fraction getopt(){
			Fraction x[this->n];
			for(int i = 0 ; i < this->n ; i++){
				Fraction tmp;
				tmp.set("0/1");
				x[i] = tmp;
			}
			cout<<"������Ϊ:"<<endl; 
			for(int i = 0 ; i < this->m ; i++){
				cout<<"x"<<this->basic_vector_list[i]+1<<" "; 
			}
			cout<<endl;
			//�Ի��������б��� 
			for(int i = 0 ; i < this->m ; i++){
				//��û������±� 
				int j = this->basic_vector_list[i];
				//��������ֵ 
				x[j] = this->b[i]; 
			}
			cout<<"���Ž�����Ϊ:"<<endl; 
			for(int i = 0 ; i < this->n ; i ++){
				cout<<x[i].result()<<" ";
			}
			cout<<endl;
			Fraction opt;//���Ž� 
			opt.set("0/1");							
			for(int i = 0 ; i < this->n ; i++){
				Fraction tmp;
				tmp.set("0/1");
				tmp= tmp.MUL(this->c[i],x[i]);
				opt = opt.ADD(opt,tmp);
			}
			cout<<"���Ž�Ϊ��"<<opt.result()<<endl;
			return  opt; 
		}
		
		//��ӡ���� 
		void Print(){
			cout<<"Լ������Ϊ��"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				for(int j = 0 ; j < this->n ; j++){
					cout<<this->A[i][j].result()<<" ";
				}
				cout<<endl;
			}
			cout<<"������Ϊ��"<<endl;
			for(int i = 0 ; i < this->n ; i++){
				cout<<this->b[i].result()<<" ";
			} 
			cout<<endl;
			cout<<"Ŀ��ϵ����c��Ϊ��"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<this->c[i].result()<<" ";
			} 
			cout<<endl;
			cout<<"Ŀ��ϵ����cb��Ϊ��"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<this->cb[i].result()<<" ";
			}
			cout<<endl<<"��������:"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<"x"<<this->basic_vector_list[i]+1<<" ";
			}
			cout<<endl;
		} 
}; 

int main()
{
	Simplex simplex; 
	simplex.Init();
	bool flag = simplex.SimplexSolve();
	if(flag){
		Fraction ans = simplex.getopt(); 	
	}else{
		cout<<"�����Ž�"<<endl; 
	}
	
	return 0;
 } 
