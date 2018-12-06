#include <iostream>
#include <string>
using namespace std;

class Fraction{
	private:
		string fenmu;			//��ĸ 
		string fenzi;			//���� 
	public:
		//������Ĺ��캯�� 
		void set(string str){
			//�ַ�����û��'/'��ֱ�ӷ�ĸ��Ϊ1������Ϊstr 
			if(str.find('/') == string::npos){
				this->fenmu = "1";
				this->fenzi = str;	
			}else{
				int index = str.find('/');		//�ҵ�'/'��λ�� 
				string fenzi = str.substr(0,index);	//0��index֮ǰΪ���� 
				string fenmu = str.substr(index+1,str.length()-index-1);	//index֮����ַ���Ϊ��ĸ 
				this->setFenmu(fenmu);
				this->setFenzi(fenzi); 
			}
		}
		
		//����������ú��� 
		void set(string fenmu,string fenzi){ 
			if(fenmu[0] == '-' && fenzi[0] == '-'){			// ���ӷ�ĸͬΪ�� 
				fenmu = fenmu.erase(0,1);
				fenzi = fenzi.erase(0,1);
			}else if(fenmu[0] == '-' && fenzi[0] != '-'){	//��ĸΪ�� ����Ϊ��
				fenmu = fenmu.erase(0,1);
				fenzi = "-"+fenzi;
			}
			if(fenzi[0] == '-'){			//����Ϊ0ʱ��ǰ���и��� 
				string tmp = fenzi.substr(1,fenzi.length()-1);
				if(tmp.compare("0") == 0){
					fenzi = tmp;
				}
			}
			this->setFenmu(fenmu);
			this->setFenzi(fenzi); 
		}
		
		//��ʼ������ 
		void setFenzi(string fenzi){
			this->fenzi = fenzi;
		}
		
		//��ʼ����ĸ 
		void setFenmu(string fenmu){
			this->fenmu = fenmu; 
		} 
		
		//��ȡ���� 
		string getFenzi(){
			return this->fenzi;
		}
		
		//��ȡ��ĸ 
		string getFenmu(){
			return this->fenmu; 
		}
		
		//����ȡ�� 
		void setOpposite(){
			int flag = this->Compare2Zero();
			//Ϊ0����Ҫ�÷�������ԭ������
			//������Ҫ���Ǹ�0����� 
			if(flag != 0){
				string fenzi = this->getFenzi();
				if(flag == -1){//Ϊ����ʱ 
					fenzi = fenzi.erase(0,1);		//ȥ��ǰ��ķ��� 
				}else if(flag == 1){//Ϊ����ʱ 
					fenzi = "-"+fenzi;
				}
				this->setFenzi(fenzi); 
			}
		}
		
		//��������
		void setReciprocal(){
			//0û�е����������迼��
			Fraction one,_one;
			one.set("1/1");
			_one.set("-1/1");
			//����Ϊ1����-1ʱ��һ����������ʱ��ֱ�Ӳ���Ҫ���з��ӷ�ĸ�任 
			if(!(this->Compare2Fraction(one) == 0 || this->Compare2Fraction(_one) == 0)){
				string fenmu = this->getFenmu();
				string fenzi = this->getFenzi();
				this->set(fenzi,fenmu); 	
			}
		} 
		
		//���ַ������ط��� 
		string result(){
			string res = this->fenzi;
			if(this->fenmu.compare("0") != 0){// 
				if(this->fenmu.compare("1") != 0){
					res = res+"/"+this->fenmu; 
				}	
			}
			return res; 
		}
		
		//���ǱȽ���������֮���С�ĺ��� 
		int compare(string str1,string str2){	
			//��ȷ���0�����ڷ���1��С�ڷ���-1
			if(str1.size()>str2.size()){
				return 1; //���ȳ����������ڳ���С������
			}else if(str1.size()<str2.size()){
				return -1;	
			}else{
				return str1.compare(str2); //��������ȣ���ͷ��β��λ�Ƚ�
			}
		}
		
		//�������������Լ�� 
		string gcd(string str1,string str2){
			int sign = 1;
			if(str1[0] ==  '-'){			// str1Ϊ������ȥ��ǰ������ 
				sign *= -1;					//��־λȡ�෴�� 
				str1 = str1.erase(0,1);		 
			}
			if(str2[0] == '-'){				// str2Ϊ������ȥ��ǰ������ 
				sign *= -1;					//��־λȡ�෴�� 
				str2 = str2.erase(0,1);
			}
			if(str1.compare("1") == 0 || str2.compare("1") == 0){		//str1��str2Ϊ1ʱ 
				if(sign == -1){				//��־λλ-1��str2�Ӹ��� 
					return "-1";		 
				}
				return "1";
			}else{				//str1��str2����Ϊ1ʱ������շת����������Լ�� 
				string gcd;
				while(str2.compare("0") != 0){
					gcd = this->MOD_INT(str1,str2);
					str1 = str2;
					str2 = gcd;
				}
				gcd = str1;
				if(sign == -1){ 
					gcd = "-"+gcd;
				} 
				return gcd;
			}
		} 
	
		//������������С������
		string gcm(string str1,string str2){
			if(str1.compare("1") == 0 || str2.compare("1") == 0){
				return "1";
			}
			if(str1.compare("-1") == 0 || str2.compare("-1") == 0){
				return "-1";
			}
			string tmp1 = str1;
			string tmp2 = str2;
			string gcd = this->gcd(tmp1,tmp2);			//�������Լ�� 
			string gcm = this->MUL_INT(str1,str2);
			gcm = this->DIV_INT(gcm,gcd);				//������С������ 
			return gcm; 
		} 
		
		//�����ӷ�
		Fraction ADD(Fraction num1,Fraction num2){
			string fenmu,fenzi,gcd;
			//num1��ĸ��Ϊ0��num1����Ϊ0��ֱ�ӷ���num2 
			if(num1.fenmu.compare("0") != 0 && num1.fenzi.compare("0") == 0){
				return num2;
			}
			//num1��ĸ��Ϊ0��num2����Ϊ0��ֱ�ӷ���num1 
			if(num2.fenmu.compare("0") != 0 && num2.fenzi.compare("0") == 0){
				return num1;
			}
			if(num1.fenmu.compare(num2.fenmu) == 0){//������ĸ��� 
				fenmu = num1.fenmu;									//������ĸ 
				fenzi = this->ADD_INT(num1.fenzi,num2.fenzi);		//������� 
				gcd = this->gcd(fenmu,fenzi);						//�������Լ��
				if(gcd.compare("1") != 0){		//���Լ����Ϊ1ʱ����Ҫ����Լ�� 
					fenmu = this->DIV_INT(fenmu,gcd);					//Լ�ֺ�ķ�ĸ
					fenzi = this->DIV_INT(fenzi,gcd);					//Լ�ֺ�ķ���					
				}
			}else{//��ĸ����� 
				string fenzi1 = this->MUL_INT(num1.fenzi,num2.fenmu);			//����ͨ�ֺ�ķ���1 
				string fenzi2 = this->MUL_INT(num2.fenzi,num1.fenmu);			//����ͨ�ֺ�ķ���2 
				fenzi = this->ADD_INT(fenzi1,fenzi2);							//������� 
				fenmu = this->MUL_INT(num1.fenmu,num2.fenmu);					//�����ĸ 
				gcd = this->gcd(fenmu,fenzi);									//������Ӻͷ�ĸ�����Լ�� 
				if(gcd.compare("1") != 0){		//���Լ����Ϊ1ʱ����Ҫ����Լ�� 
					fenmu = this->DIV_INT(fenmu,gcd);								//����ͨ�ֺ�ķ�ĸ
					fenzi = this->DIV_INT(fenzi,gcd);								//����ͨ�ֺ�ķ��� 	
				}
			}
			Fraction result;
			result.set(fenmu,fenzi); 
			return result;
		}
		
		//��������
		Fraction SUB(Fraction num1,Fraction num2){
			//num1Ϊ0ʱ������num2���෴�� 
			if(num1.getFenmu().compare("0") != 0 && num1.getFenzi().compare("0") == 0){
				num2.setOpposite(); 
				return num2;
			}
			//num2Ϊ0ʱ������num1 
			if(num2.getFenmu().compare("0") != 0 && num2.getFenzi().compare("0") == 0){
				return num1;
			}
			string fenmu,fenzi,gcd; 
			if(num1.getFenmu().compare(num2.fenmu) == 0){//������ĸ��� 
				fenmu = num1.getFenmu();									//������ĸ 
				fenzi = this->SUB_INT(num1.getFenzi(),num2.getFenzi());		//������� 
				gcd = this->gcd(fenmu,fenzi);						//�������Լ�� 
				if(gcd.compare("1") != 0){		//���Լ����Ϊ1ʱ����Ҫ����Լ�� 
					fenmu = this->DIV_INT(fenmu,gcd);					//Լ�ֺ�ķ�ĸ
					fenzi = this->DIV_INT(fenzi,gcd);					//Լ�ֺ�ķ���	
				}
			}else{//��ĸ����� 
				string fenzi1 = this->MUL_INT(num1.fenzi,num2.fenmu);			//����ͨ�ֺ�ķ���1 
				string fenzi2 = this->MUL_INT(num2.fenzi,num1.fenmu);			//����ͨ�ֺ�ķ���2 
				fenzi = this->SUB_INT(fenzi1,fenzi2);							//������� 
				fenmu = this->MUL_INT(num1.fenmu,num2.fenmu);					//�����ĸ 
				gcd = this->gcd(fenmu,fenzi);									//������Ӻͷ�ĸ�����Լ�� 
				if(gcd.compare("1") != 0){			//���Լ����Ϊ1ʱ����Ҫ����Լ�� 
					fenmu = this->DIV_INT(fenmu,gcd);								//����ͨ�ֺ�ķ�ĸ
					fenzi = this->DIV_INT(fenzi,gcd);								//����ͨ�ֺ�ķ��� 	
				}
			}
			Fraction result;
			result.set(fenmu,fenzi);
			return result;
		}
		
		//�����˷�
		Fraction MUL(Fraction num1,Fraction num2){
			string fenmu,fenzi;
			//������ĸ������һ��0ʱ��ֱ�ӷ��������("9999999/1") 
			if(num1.fenmu.compare("0") == 0|| num2.fenmu.compare("0") == 0){
				Fraction result;
				result.set("9999999/1");
				return result;
			} 
			//��������������һ��0ʱ��ֱ�ӷ���0 
			if(num1.fenzi.compare("0") == 0|| num2.fenzi.compare("0") == 0){		//���ӳ���0ʱ��ֱ�ӷ���0 
				Fraction result;
				result.set("0/1");
				return result;
			}
			//�����ĸ 
			if(num1.fenmu.compare("1") == 0 && num2.fenmu.compare("1") == 0){			//������ĸȫΪ1 
				fenmu = "1"; 
			}else if(num1.fenmu.compare("1") == 0 && num2.fenmu.compare("1") != 0){		//num1��ĸΪ1 
				fenmu = num2.fenmu;
			}else if(num1.fenmu.compare("1") != 0 && num2.fenmu.compare("1") == 0){		//num2��ĸΪ1 
				fenmu = num1.fenmu;
			}else{			//������ĸ����Ϊ1 
				fenmu = this->MUL_INT(num1.fenmu,num2.fenmu);
			}
			//�������
			if(num1.fenzi.compare("1") == 0 && num2.fenzi.compare("1") == 0){			//��������ȫΪ1 
				fenzi = "1"; 
			}else if(num1.fenzi.compare("1") == 0 && num2.fenzi.compare("1") != 0){		//num1����Ϊ1 
				fenzi = num2.fenzi; 
			}else if(num1.fenzi.compare("1") != 0 && num2.fenzi.compare("1") == 0){		//num2����Ϊ1 
				fenzi = num1.fenzi; 
			}else{			//�������Ӷ���Ϊ1 
				fenzi = this->MUL_INT(num1.fenzi,num2.fenzi);
			}
			//��ĸ����Ϊ1,�ҷ��Ӳ�Ϊ0ʱ������Ҫ����Լ�� 
			if(fenmu.compare("1") != 0 && fenzi.compare("1") != 0){
				string gcd = this->gcd(fenmu,fenzi);
				if(gcd.compare("1") != 0){		//���Լ����Ϊ1ʱ����Ҫ����Լ�� 
					fenmu = this->DIV_INT(fenmu,gcd);								//����ͨ�ֺ�ķ�ĸ
					fenzi = this->DIV_INT(fenzi,gcd);								//����ͨ�ֺ�ķ��� 	
				}
			}
			Fraction result;
			result.set(fenmu,fenzi); 
			return result; 
		} 
		
		//��������
		Fraction DIV(Fraction num1,Fraction num2){
			// num1Ϊ0ʱ 
			if(num1.fenmu.compare("0") != 0 && num1.fenzi.compare("0") == 0){
				Fraction result;
				result.set("0/1");
				return result;
			}
			//num2Ϊ1ʱ
			if(num2.fenmu.compare("1") == 0 && num2.fenzi.compare("1") == 0){
				return num1;
			}
			//num2Ϊ0ʱ�����ǽ������ʼ��Ϊ"9999999/1" 
			if(num2.fenmu.compare("1") == 0 && num2.fenzi.compare("0") == 0){
				Fraction result;
				result.set("9999999/1");
				return result;
			}
			Fraction tmp; 
			string fenmu = num2.getFenmu();
			string fenzi = num2.getFenzi();
			tmp.set(fenmu,fenzi);
			tmp.setReciprocal();	//���㵼�� 
			//����ת��Ϊ�˷� 
			return tmp.MUL(num1,tmp);
		} 
		
		//�����ӷ� 
		string ADD_INT(string str1,string str2){
			//str1Ϊ0������str2 
			if(str1.compare("0") == 0){
				return str2;
			}
			//str2Ϊ0������str1
			if(str2.compare("0") == 0){
				return str1;
			}
			//�߾��ȼӷ�
		    int sign=1; //sign Ϊ����λ
		    string str;
		    if(str1[0]=='-'){	//str1Ϊ���� 
				if (str2[0]=='-'){	//str2Ϊ���� 
					sign=-1;	//-1��������������� 
		            // ȥ���������ź���� 
					str=ADD_INT(str1.erase(0,1),str2.erase(0,1));
		        }else{//str2Ϊ����
					//ȥ��str1�ķ��ţ�ת��Ϊ���� 
		            str=SUB_INT(str2,str1.erase(0,1));
		        }
		    }else{	// str1Ϊ���� 
		        if(str2[0]=='-'){	//str2Ϊ���� 
		        	// ȥ��str2�ĸ�����ת��Ϊ���� 
		            str=SUB_INT(str1,str2.erase(0,1));
		        }else{	//str2Ϊ���� 
					//�������������룬������ǰ���0����
		            string::size_type L1,L2;
		            int i;
		            L1=str1.size();
		            L2=str2.size();
		            if(L1<L2){	// str1�ĳ��ȱ�str2С��str1��ǰ����0 
		                for(i=1;i<=L2-L1;i++){
		                	str1="0"+str1;	
						}
		            }else{	// str2�ĳ��ȱ�str2С��str2��ǰ�油��0 
		                for(i=1;i<=L1-L2;i++){
		                	str2="0"+str2;	
						}
		            }
		            int int1=0,int2=0; //int2 ��¼��λ��int1��¼��� 
		            for(i=str1.size()-1;i>=0;i--){
		                int1=(int(str1[i])-'0'+int(str2[i])-'0'+int2)%10;
		                int2=(int(str1[i])-'0'+int(str2[i])-'0'+int2)/10;
		                str=char(int1+'0')+str;
		            }
		            if(int2!=0){	//����������н�λ��ֱ����ǰ�油�� 
		            	str=char(int2+'0')+str;	
					}
		        }
		    }
		    //����������λ
		    if((sign==-1)&&(str[0]!='0')){
		    	str="-"+str;	
			}
		    return str;
		}
		
		//�������� 
		string SUB_INT(string str1,string str2){
			//str1Ϊ0������str2 
			if(str1.compare("0") == 0){
				//str2Ϊ���� 
				if(str2.compare("0") == 1){
					return "-"+str2; 
				}else if(str2.compare("0") == 0){
					return "0";
				}else{
					return str2.erase(0,1);
				}
			}
			//str2Ϊ0������str1 
			if(str2.compare("0") == 0){
				return str1;
			}	
			//�߾��ȼ���
		    int sign=1; //signΪ����λ
		    string str;
		    int i,j;
			if(str2[0]=='-'){	//str2Ϊ����
				// ȥ��str2�ķ��ţ�ת��Ϊ�ӷ� 
		        str=ADD_INT(str1,str2.erase(0,1));
		    }else{	// str2Ϊ����
		    	if(str1[0] == '-'){		//str1Ϊ������ת��Ϊ�ӷ� 
		    		str = ADD_INT(str1.erase(0,1),str2);
		    		str = "-"+str;
				}else{	//str1Ϊ���� 
					// �ж�str1��str2��С 
			        int res=compare(str1,str2);
			    	//cout<<"==="<<res<<endl; 
			        if(res==0){		//str1��str2��� 
						return "0";	
					}
			        if(res<0){	//str1С��str2 
			            sign=-1;	//��־λ��Ϊ-1
						// str1��str2���� 
			            string temp =str1;
			            str1=str2;
			            str2=temp;
			        }
			        string::size_type tempint; 
			        tempint=str1.size()-str2.size();
			        // ��ֵ��С�ߵĽ��б�����tempint=0˵��������ȣ�����0��str1���ȴ���str2 
			        // �����һλ��ʼ���� 
			        for(i=str2.size()-1;i>=0;i--){
			        	// str1�Ķ�ӦΪС��str2�Ķ�Ӧλ 
			            if(str1[i+tempint]<str2[i]){
			                j=1;	//ƫ��λ
							//��ʼѭ������ʼѰ�ҽ�λ 
			                while(1){
			                	//ǰ���λΪ0����1�ó�9 
								if(str1[i+tempint-j]=='0'){
			                        str1[i+tempint-j]='9';
			                        j++;
			                    }else{//ǰ���λΪ0����1����ǰλ��1 
			                        str1[i+tempint-j]=char(int(str1[i+tempint-j])-1);
			                        break;
			                    }
			                }
			                str=char(str1[i+tempint]-str2[i]+':')+str;
			            }else{
			                str=char(str1[i+tempint]-str2[i]+'0')+str;
			            }
			        }
			        //�Ѷ���Ϊ������ǰ����
			        for(i=tempint-1;i>=0;i--){
			        	str=str1[i]+str;	
					}
				}
			}
		    //ȥ������ж����ǰ��0
		    str.erase(0,str.find_first_not_of('0'));
		    if(str.empty()){
		    	str="0";	
			}
		    if((sign==-1) && (str[0]!='0')){
		    	str ="-"+str;	
			}
		    return str;
		}
		
		//�����˷� 
		string MUL_INT(string str1,string str2){
			//str1��str2���ٴ���1��0��ֱ�ӷ���0 
			if(str1.compare("0") == 0 || str2.compare("0") == 0){
				return "0";
			}
			//str1Ϊ1ֱ�ӷ���str2 
			if(str1.compare("1") == 0){
				return str2; 
			}
			//str2Ϊ1ֱ�ӷ���str1
			if(str2.compare("1") == 0){
				return str1; 
			}
			//str1Ϊ-1
			if(str1.compare("-1") == 0){
				//str2Ϊ���� 
				if(str2.compare("0") < 0){
					return str2.erase(0,1);
				}else{
					//str2Ϊ���� 
					return "-"+str2; 	
				}
			}
			//str2Ϊ1
			if(str2.compare("-1") == 0){
				//str1Ϊ���� 
				if(str1.compare("0") < 0){
					return str1.erase(0,1);
				}else{
					//str1Ϊ���� 
					return "-"+str1;	
				}  
			}
			//�߾��ȳ˷�
		    int sign=1; //sign Ϊ����λ
		    string str;
		    // str1Ϊ���� 
		    if(str1[0]=='-'){
		        sign*=-1;	// ��־λ��-1
		        str1 =str1.erase(0,1);	// ȥ������ 
		    }
		    // str2Ϊ���� 
		    if(str2[0]=='-'){
		        sign*=-1;					// ��־λ��-1
		        str2 =str2.erase(0,1); 		// ȥ������ 
		    }
		    int i,j;
		    string::size_type L1,L2;
		    L1=str1.size();
		    L2=str2.size();
		    for(i=L2-1;i>=0;i--){ //ģ���ֹ��˷���ʽ
		        string tempstr;
		        int int1=0,int2=0,int3=int(str2[i])-'0';
		        if(int3!=0){
		        	// �����ѭ��ʵ�ֽ����˲�0���� 
		            for(j=1;j<=(int)(L2-1-i);j++){
		            	tempstr="0"+tempstr;	
					}
		            for(j=L1-1;j>=0;j--){
		            	// int1��¼��λ����int��¼ʮλ�� 
		                int1=(int3*(int(str1[j])-'0')+int2)%10;
		                int2=(int3*(int(str1[j])-'0')+int2)/10;
		                tempstr=char(int1+'0')+tempstr;
		            }
		            if(int2!=0){
		            	tempstr=char(int2+'0')+tempstr;	
					}
		        }
		        // ��ǰ�����tempstr�� 
		        str=ADD_INT(str,tempstr);
		    }
		    //ȥ������е�ǰ��0
		    str.erase(0,str.find_first_not_of('0'));
		    if(str.empty()){
		    	str="0";	
			}
		    if((sign==-1) && (str[0]!='0')){
		    	str="-"+str;	
			}
		    return str;
		}
		
		//�������� 
		string DIVIDE_INT(string str1,string str2,int flag){
			//�߾��ȳ�����flag==1ʱ,������; flag==0ʱ,��������
		    string quotient,residue; //�����̺�����
		    int sign1=1,sign2=1;
		    if(str2 == "0"){  //�жϳ����Ƿ�Ϊ0
		        quotient= "ERROR!";
		        residue = "ERROR!";
		        if(flag==1){
		        	return quotient;	
				}else{
					return residue;	
				}
		    }
		    //�жϱ������Ƿ�Ϊ0
			if(str1=="0"){
				quotient="0";
				residue ="0";
				if(flag == 1){
					return quotient;
				}else{
					return residue;
				}
			}
			//������Ϊ1��ֱ�ӷ���str1 
			if(str2 == "1"){
				quotient = str1;
				residue = "0";
				if(flag == 1){
					return quotient;
				}else{
					return residue;
				}
			}
			//������Ϊ-1 
			if(str2 == "-1"){
				if(str1.compare("0") < 0){
					quotient = str1.erase(0,1);
				}else{
					quotient = "-"+str1;
				}
				residue = "0";
				if(flag == 1){
					return quotient;
				}else{
					return residue;
				}
			}
		    // str1Ϊ���� 
		    if(str1[0]=='-'){
		        str1 = str1.erase(0,1);		//ȥ��ǰ��0 
		        sign1 *= -1;
		        sign2  = -1;
		    }
		    // str2Ϊ���� 
		    if(str2[0]=='-'){
		        str2 = str2.erase(0,1);		//ȥ��ǰ��0 
		        sign1 *= -1;
		    }
		    //�Ƚ�str1��str2�Ĵ�С 
		    int res=compare(str1,str2);
		    // str1С��str2 
		    if(res<0){
		    	// ��Ϊ0������Ϊstr1 
		        quotient="0";
		        residue =str1;
		    }else if(res == 0){
		    	// str1��str2���,��Ϊ1������Ϊ0 
		        quotient="1";
		        residue ="0";
		    }else{
		    	// str1����str2 
		        string::size_type L1,L2;
		        L1=str1.size();
		        L2=str2.size();
		        string tempstr;
		        tempstr.append(str1,0,L2-1);
		        for(int i=L2-1;i<L1;i++){ //ģ���ֹ�������ʽ
		            tempstr=tempstr+str1[i];
		            //���ܳ��ֲ��������������ô�����ǰ��0ȥ�� 
		            tempstr.erase(0,tempstr.find_first_not_of('0'));
		            if(tempstr.empty()){
						tempstr="0";
					}
		        	for(char ch='9';ch>='0';ch--){ //����
		                string str;
		                str=str+ch;
		                if(compare(MUL_INT(str2,str),tempstr)<=0){
		                    quotient=quotient+ch;
		                    tempstr =SUB_INT(tempstr,MUL_INT(str2,str));
		                    break;
		                }
		            }
		        }
		        residue=tempstr;
		    }
		    //ȥ������е�ǰ��0
		    quotient.erase(0,quotient.find_first_not_of('0'));
		    if(quotient.empty()){
		    	quotient="0";	
			}
		    if((sign1==-1)&&(quotient[0]!='0')){
		    	quotient="-"+quotient;	
			}
		    if((sign2==-1)&&(residue [0]!='0')){
		    	residue ="-"+residue ;	
			}
			if(flag==1){
		    	return quotient;	
			}else{
				return residue;	
			}
		}
		
		//���������������� 
		string DIV_INT(string str1,string str2){
			//�߾��ȳ���,������
		    return DIVIDE_INT(str1,str2,1);
		}
		
		//����������������� 
		string MOD_INT(string str1,string str2){
			//�߾��ȳ���,��������
		    return DIVIDE_INT(str1,str2,0);
		}
		
		//�жϷ�����0�Ĵ�С 
		int Compare2Zero(){
			int sign_fenzi = 1;
			int sign_fenmu = 1;
			int sign = 1;		//��¼�Ƿ���Ӻ��и��� 
			string fenzi = this->fenzi;
			string fenmu = this->fenmu; 
			if(fenzi[0] == '-'){	//����Ϊ����ʱ���ı��־λ 
				sign_fenzi = -1;
				fenzi = fenzi.erase(0,1);
			}
			if(fenmu[0] == '-'){	//����Ϊ����ʱ���ı��־λ  
				sign_fenmu = -1;
				fenmu = fenmu.erase(0,1);
			} 
			int ans_fenzi = this->compare(fenzi,"0");		//�ȽϷ��ӵľ���ֵ��0�Ĵ�С 
			int ans_fenmu = this->compare(fenmu,"0");		//�ȽϷ�ĸ�ľ���ֵ��0�Ĵ�С 
			if(sign_fenzi == -1 && ans_fenzi == 1){
				ans_fenzi = -1;
			}
			if(sign_fenmu == -1 && ans_fenmu == 1){
				ans_fenmu = -1;
			}
			int flag;
			if(ans_fenzi == 0 && ans_fenmu != 0){		//����Ϊ0����ĸ��Ϊ0������0 
				flag = 0;
			}
			if(ans_fenzi*ans_fenmu > 0){				//���ӷ�ĸͬ�ţ�����1 
				flag = 1;	
			}
			if(ans_fenzi*ans_fenmu < 0){				//���ӷ�ĸ��ţ�����-1 
				flag = -1;								
			}
			return flag;
		}
		
		//��������֮��ıȽ�
		int Compare2Fraction(Fraction fraction){
			Fraction ans,tmp;
			tmp.set(this->getFenmu(),this->getFenzi());
			//����Ľ����0���ԱȾ�����������֮��Ĵ�С��ϵ 
			ans = ans.SUB(tmp,fraction); 
			return ans.Compare2Zero();	//����������֮�����0�Ĵ�С�ȽϽ�� 
		} 
};
