#include <iostream>
#include <string>
#include <cstring>
#include <set>
#include <algorithm>
#include <E:\�о���\�˳�ѧ\���׶η�\Fraction.h>
using namespace std;

const long long SIZE = 100;

class Two_Stages_Simplex{
	private: 
		Fraction stage_one_c[SIZE]; 						 //�׶�һĿ�꺯��ϵ�� 
		Fraction stage_two_c[SIZE]; 						//�׶ζ�Ŀ�꺯��ϵ��
		Fraction c[SIZE]; 						 			//�׶�һĿ�꺯��ϵ�� 
		int m;												//Լ���������� 
		int n;						   		   			   //�������� 
		Fraction A[SIZE][SIZE];				  			  //Լ��ϵ������ 
		Fraction b[SIZE];					 			 //���������
		Fraction cb[SIZE];							   //��������Ӧ��Ŀ��ϵ�� 
		Fraction theta[SIZE];			 			  //�������뻻��Լ������������������Ľ��
		int basic_vector_list[SIZE];				 //�����б� 
		int type;									//��¼Լ��Ŀ�����ͣ�-1������С����1�������
		int isuse[SIZE];							//�˹������Ƿ�ʹ�ñ�־���������Ƶ�һ�͵ڶ��׶ε��˹�����
		set<int> artificai_variable_set;			//�˹��������� 
	public:
		//��ʼ�����Թ滮Ŀ�꺯����Լ������ 
		void Init(){
			//���ȳ�ʼ�����ϵ������
			for(int i = 0 ; i < SIZE ; i++){
				for(int j = 0 ; j < SIZE ; j++){
					this->A[i][j].set("0/1");
				}
				this->b[i].set("0/1");
				this->stage_one_c[i].set("0/1");
				this->stage_two_c[i].set("0/1");
				this->isuse[i] = 1; 
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
			int cnt = 0;	//�ɳڱ������˹����������� 
			for(int i = 0 ; i < m ; i++){
				cout<<"���벻��ʽ"<<i+1<<":";
				for(int j = 0 ; j < n ; j++){
					string str;
					cin>>str;
					this->A[i][j].set(str);
				}
				//���벻��ʽ����ͳ����� 
				string _b;		//������ 
				cin>>direction>>_b;
				this->b[i].set(_b);		//�������ʼ��
				Fraction relaxation_variable;
				relaxation_variable.set("1/1");	//���Ⱥ�Ϊ<=ʱ��ϵ����Ϊ1
				if(direction == 0){//���Ⱥ�Ϊ=ʱ 
					Fraction artificial_variable,artificial_c;
					artificial_variable.set("1/1");
					artificial_c.set("-1/1");
					this->A[i][this->n+cnt] = artificial_variable;//�����˹����� 
					this->stage_one_c[this->n+cnt] = artificial_c;//�˹������ĵ�һ�׶ε�Ŀ��ϵ����Ϊ-1
					this->artificai_variable_set.insert(this->n+cnt);		//�˹��������±���뼯��(�±��Ǵ�0��ʼ) 
					cnt++;
				}else if(direction == 1){//���Ⱥ�Ϊ>=ʱ
					if(this->b[i].Compare2Zero() == -1){//������Ϊ����ʱ 
						this->b[i].setOpposite();		//������ȡ��
						for(int j = 0 ; j < this->n; j++){//����ϵ��ȡ�� 
							this->A[i][j].setOpposite();
						}
						this->A[i][this->n+cnt] = relaxation_variable;	//�����ɳڱ��� 
						cnt++;
					}else{	//�����С��0ʱ 
						relaxation_variable.setOpposite();	//�ɳڱ���ϵ����Ϊ-1
						this->A[i][this->n+cnt] = relaxation_variable;	//�����ɳڱ��� 
						cnt++;	
						//this->loose_variable_cnt++;
						Fraction artificial_variable,artificial_c;
						artificial_variable.set("1/1");		//�����˹����� 
						artificial_c.set("-1/1");			//�˹�������Ӧ��Ŀ��ϵ�� 
						this->A[i][this->n+cnt] = artificial_variable;//�����˹����� 
						this->stage_one_c[this->n+cnt] = artificial_c;//�˹������ĵ�һ�׶ε�Ŀ��ϵ����Ϊ-1
						this->artificai_variable_set.insert(this->n+cnt);//�˹��������±���뼯��(�±��Ǵ�0��ʼ) 
						cnt++;
					}
				}else{//���Ⱥ�Ϊ<=ʱ 
					this->A[i][this->n+cnt] = relaxation_variable;	//�����ɳڱ��� 
					cnt++;
				}
			} 
			cout<<"������Ŀ�꺯���Ż����ͺ�Ŀ�꺯��ϵ������(����ֵΪ1�������,-1������С)"<<endl; 
			cout<<"������Ŀ�꺯���Ż����ͣ�"<<endl; 
			cin>>type;
			this->type = type;
			cout<<"������Ŀ�꺯��ϵ����"<<endl;
			for(int i = 1 ; i <= n ; i++){
				cout<<"\tx"<<i;
			}
			cout<<endl;
			for(int i = 0 ; i < this->n ; i++){
				this->stage_one_c[i].set("0/1");
				this->stage_two_c[i].set("0/1");
				this->cb[i].set("0/1");
			}
			for(int i = 0 ; i < n ; i++){
				string str;
				cin>>str;
				this->stage_two_c[i].set(str);
				if(this->type == -1){// ��Ŀ�꺯��������Сֵʱ��Ҫ����ģ��ת����ת��Ϊ���ֵ 
					this->stage_two_c[i].setOpposite();
				}
				this->basic_vector_list[i] = i; 
			}
			//���µ�ǰ�ı������� 
			this->n += cnt; 
			//���в��Ⱥų��֣���Ҫ�����ɳڱ�������ӦĿ��Լ��ϵ����Ϊ0 
			for(int i = n ; i < this->n ; i++){
				this->cb[i].set("0/1");
				this->basic_vector_list[i] = i; 
			}
		}
		
		bool Two_Stage_Simplex_Solve(){
			//��һ�׶εĽ�� 
			cout<<"���׶��㷨�ĵ�һ�׶Σ�"<<endl;
			bool ans = this->first_stage_solve();
			if(ans){//Ϊ����������еڶ��׶� 
				cout<<"���׶��㷨�ĵڶ��׶Σ�"<<endl;
				ans = this->second_stage_solve(); 
			}
			return ans; 
		}
		
		//���׶��㷨�ĵ�һ�׶� 
		bool first_stage_solve(){
			//flag[i]�Ǽ�¼��i���Ƿ�Ϊ��λ����,index[i]��¼��i����Ϊ��λ����ʱ1���±� 	
			int flag[this->n],index[this->n];
			//���ȶ�Ŀ��ϵ�����и�ֵ 
			for(int i = 0 ; i < this->n ; i++){
				this->c[i] = this->stage_one_c[i];
			} 
			//Ѱ��m����λ������
			this->FindUnitVector(flag,index,n);
			return this->SimplexSolve();		//ִ�е�һ�׶ε������㷨 
		} 
		
		//���׶��㷨�ĵڶ��׶�
		bool second_stage_solve(){ 
			//���˹��������óɲ����� 
			Fraction one;
			one.set("-1/1");
			for(int i = 0 ; i < this->n ; i++){
				if(this->stage_one_c[i].Compare2Fraction(one) == 0){//���˹����� 
					this->isuse[i] = 0;
				}
			}
			//����cb 
			for(int i = 0 ; i < this->m ; i++){
				this->cb[i] = this->stage_two_c[this->basic_vector_list[i]];
			}
			//����c
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){//��һ�׶ε��˹������ڵڶ��׶����� 
					continue;
				}
				this->c[i] = this->stage_two_c[i]; 
			}
			return this->SimplexSolve();		//���еڶ��׶εĵ������㷨 
		} 
		
		//Ѱ�ҵ�λ���������Ի������б�cb���и�ֵ 
		void FindUnitVector(int* flag,int* index,int n){
			//Ѱ�ҵ�λ������ 
			int cnt = 0;		//��¼��λ���������� 
			for(int i = this->n-1 ; i >= 0 ; i--){
				//�жϵ�i���Ƿ�λ���� 
				int _index = this->isUnitVector(i);
				if(_index == -1){//���ǵ�λ������ 
					flag[i] = 0;
					index[i] = -1; 
				}else{
					flag[i] = 1;
					index[i] = _index;
					//���μ�¼������ 
					this->basic_vector_list[cnt++] = i; 
				} 
			}
			//�Ի������������� 
			sort(basic_vector_list,basic_vector_list+this->m);
			//cnt��m��� 
			for(int i = 0 ; i < cnt ; i++){//��cb���и�ֵ 
				this->cb[i] = this->c[this->basic_vector_list[i]];
			}	
		}
		
		//���Թ滮��׼�͵������㷨�ⷨ 
		bool SimplexSolve(){
			bool ans;
			//�͵������㷨��ͬ�����׶��㷨��һ�׶��У������ɳ�(����)�������˹������Ĵ���
			//�˹��������ɳڱ�����Ӧ��Լ��ϵ��һ���ǵ�λ�����������û�б�Ҫ�񵥴����㷨
			//��Ҫ��Լ��������г��ȱ任���Ӷ��任����λ����������ֻ��Ҫ�ҳ���ʼ���л�
			//����Ŀ��ϵ�����ɡ�֮��ִ�е������㷨 
			//�����������Ĭ�ϱ任�ɵ�λ���Է��㵥�����㷨����ؾ������
			//��ʼ����ʽ���� 
			Fraction test_array[this->n];
			for(int i = 0 ; i < this->n ; i++){
				test_array[i].set("0/1");
			}
			while(1){
				this->Print();
				//�������������(��ʽ)
				this->ComputeTestNumber(test_array,this->n);
				cout<<endl<<"������Ϊ��"<<endl;
				for(int i = 0 ; i < this->n ; i++){
					cout<<test_array[i].result()<<" ";
				}
				cout<<endl;
				//�жϵ�ʽ�Ƿ�ȫС��0
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
						//�������Ѿ�ת��Ϊ��˵�λ������˼��˾�������
						//Ѱ��theta��������0�ķ�������С�ķ��� (���±�)
						int r = this->Find_Min_x(this->theta,this->m);
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
		
		//�������������ʽ�� 
		void ComputeTestNumber(Fraction* test_array,int n){
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					test_array[i].set("0/1"); 
				} 
				test_array[i] = this->c[i];
				for(int j = 0 ; j < this->m ; j++){
					Fraction tmp;
					tmp = tmp.MUL(this->cb[j],this->A[j][i]);
					test_array[i] = test_array[i].SUB(test_array[i],tmp);
				}
			} 
		}
		
		//�ж��������Ƿ�ȫΪ0
		int isAllLessZero(Fraction* array,int size){
			int flag = 1;
			for(int i = 0 ; i < size ; i++){
				//isuse[i]�ǵ�i�������Ƿ��ܱ�ʹ�ã�������ǵڶ��׶����˹���������ʹ��
				if(this->isuse[i] == 0){//�˹�������������  
					continue;
				}
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
				//isuse[i]�ǵ�i�������Ƿ��ܱ�ʹ�ã�������ǵڶ��׶����˹���������ʹ��
				if(this->isuse[i] == 0){//�˹������������� 
					continue;
				}
				if(test_array[i].Compare2Zero() <= 0){//������0�ļ��������� 
					continue;
				}else{//����������0ʱ
					int flag = test_array[i].Compare2Fraction(max);
					if(flag == 1){//��ǰ��������max�󣬸���max���±� 
						max = test_array[i];
						index = i;
					}
				}
			}
			return index;		//�����±� 
		}
		
		//Ѱ�ҳ���С��ֵ��Ӧ���±� 
		int Find_Min_x(Fraction* theta,int size){
			int index = 0;
			Fraction min;
			min.set("9999999/1");			//����Ϊ�������� 
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
			}
			return index;		//�����±� 
		}
		
		//Ѱ�һ������б���k���ڵ��±� 
		int Find_BasicVector_Index(int k){
			for(int i = 0 ; i < this->m ; i++){
				if(this->basic_vector_list[i] == k){
					return i;
				}
			} 
		}	
				
		//��Լ�������������볣��������Ľ�� 
		void Divide_Array(Fraction* pk,int size){
			for(int i = 0 ; i < size ; i++){
				//����Fraction�ж��ڳ���Ϊ0�Ľ������Ϊ"9999999/1"
				this->theta[i] = this->theta[i].DIV(this->b[i],pk[i]);
			}
		}
		
		//A[row][col]��λ��Ԫ��Լ��������г��ȱ任����A[row][col]��λ��Ԫ��,
		//����ת��Ϊ1����������Ϊת��Ϊ0�������������Լ����������Ӧ���� 
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
						if(this->isuse[j] == 0){
							continue;
						}
						tmp = tmp.MUL(this->A[row][j],rate);
						this->A[i][j] = this->A[i][j].SUB(this->A[i][j],tmp);
					}
					//�Գ�������б任 
					tmp = tmp.MUL(this->b[row],rate);
					this->b[i] = this->b[i].SUB(this->b[i],tmp);
				}
			} 
		}
		
		//�������Ž� 
		Fraction getopt(){
			//��ʼ�����Ž�����Ϊ0 
			Fraction x[this->n];
			for(int i = 0 ; i < this->n ; i++){
				Fraction tmp;
				tmp.set("0/1");
				x[i] = tmp;
			}
			cout<<"������Ϊ:"<<endl; 
			for(int i = 0 ; i < this->m ; i++){
				cout<<"\t"<<"x"<<this->basic_vector_list[i]+1; 
			}
			cout<<endl;
			//��ȡ���Ž����� 
			for(int i = 0 ; i < this->m ; i++){
				//��û������±� 
				int j = this->basic_vector_list[i];
				//��������ֵ 
				x[j] = this->b[i]; 
			}
			cout<<"���Ž�����Ϊ:"<<endl; 
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\t"<<"x"<<i+1; 
			}
			cout<<endl;
			for(int i = 0 ; i < this->n ; i ++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\t"<<x[i].result();
			}
			cout<<endl;
			Fraction opt;//���Ž� 
			opt.set("0/1");	
			//��������ֵ						
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				} 
				Fraction tmp;
				tmp= tmp.MUL(this->c[i],x[i]);
				opt = opt.ADD(opt,tmp);
			}
			//��Ŀ������С�������ڵ����������㷨�ǽ��׼�ͣ�
			//�����Ҫ�ڶԽ��ȡ�෴�� 
			if(this->type == -1){
				opt.setOpposite();
			}
			cout<<"Ŀ��ϵ��Ϊ��"<<endl; 
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\t"<<"c"<<i+1; 
			}
			cout<<endl;
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				if(type == -1){
					this->c[i].setOpposite();	
				}
				cout<<"\t"<<this->c[i].result(); 
			} 
			cout<<endl;
			cout<<"���Ž�Ϊ��"<<opt.result()<<endl;
			return  opt; 
		}
		
		//��ӡ���� 
		void Print(){
			cout<<"Լ������Ϊ��"<<endl;
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				} 
				cout<<"\t"<<"x"<<i+1; 
			}
			cout<<endl;
			for(int i = 0 ; i < this->m ; i++){ 
				for(int j = 0 ; j < this->n ; j++){
					if(this->isuse[j] == 0){
						continue;
					}
					cout<<"\t"<<this->A[i][j].result();
				}
				cout<<endl;
			}
			cout<<"������Ϊ��"<<endl;
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\t"<<this->b[i].result();
			} 
			cout<<endl;
			cout<<"Ŀ��ϵ����c��Ϊ��"<<endl;
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\tx"<<i+1; 
			}
			cout<<endl;
			for(int i = 0 ; i < this->n ; i++){
				if(this->isuse[i] == 0){
					continue;
				}
				cout<<"\t"<<this->c[i].result();
			} 
			cout<<endl;
			cout<<"Ŀ��ϵ����cb��Ϊ��"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<"\tx"<<this->basic_vector_list[i]+1;
			} 
			cout<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<"\t"<<this->cb[i].result();
			}
			cout<<endl<<"��������:"<<endl;
			for(int i = 0 ; i < this->m ; i++){
				cout<<"\tx"<<this->basic_vector_list[i]+1;
			}
			cout<<endl;
		} 
};

int main()
{
	Two_Stages_Simplex two_stages_simplex; 
	while(1){
		two_stages_simplex.Init();
		bool flag = two_stages_simplex.Two_Stage_Simplex_Solve();
		if(flag){
			Fraction ans = two_stages_simplex.getopt(); 	
		}else{
			cout<<"�����Ž�"<<endl; 
		}	
	}
	
	return 0;
 } 
