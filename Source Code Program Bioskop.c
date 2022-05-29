#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

typedef struct daftar{ //struct untuk linkedlist.
	char film[30];
	char jam[10];
	char  bookid[10];
	int seat;
	char studio[5];
	char nama[30];
	struct daftar *next,*prev;
}daftar;

typedef struct jadwal{ //struct untuk daftar film.
	char judul[40];
	char jam[10];
	char pukul[10];
	char time[10];
	char waktu[10];
	char studio[5];

}jadwal;

typedef struct spemb{ //struct untuk queue.
	char film[30];
	char jam[10];
	char  bookid[10];
	int seat;
	char studio[5];
	char nama[30];
	struct spemb *next;
}spemb; 

typedef struct tree// struct untuk daftar pekerja
{
	int code;
    char nama[30];
	char jabatan[10];	
    struct tree *left,*right;
}tree;

void cetakgambar(); // function untuk menampilkan display nama aplikasi

int isEmpty (spemb *queue); // function untuk mengecek queue kosong/tidak

void enqueue(spemb **headque, spemb **tailque,  spemb *pt); // function untuk memasukkan data ke dalam queue

void dequeue (spemb **headque); // function untuk menghapus data dari queue

spemb *front(spemb *queue); // function untuk mengetahui data yang ada di front queue

tree *newNode(int item,char nama1[30],char jab[10]); // function untuk membuat node baru pada tree

tree *insert(tree *node,tree *coba,int d); // function untuk memasukkan data ke dalam tree

void search(daftar *head, daftar *tail, daftar *node,char *cadfilm,char *cadjam,int takenseat[96]); // function untuk searching data tempat duduk yang sudah ditempati

void menupembelian(daftar *head, daftar *tail); // function yang menunjukkan menu pembelian, pada function ini customer bisa memilih film yang ingin ditonton

void pembatalan(daftar *head, daftar *tail); // function yang berfungsi membatalkan pembelian tiket

void pembayaran(daftar *head, daftar *tail, daftar *node); // function yang mengarahkan customer ke proses pembayaran

void pembeliantiket(jadwal *q,int i); // function yang mengarahkan customer ke detail film, waktu tayang, dan pemilihan tempat duduk

void printfilm(daftar *head, daftar *tail); // function yang berfungsi mencetak daftar film

void printlinked1(daftar *head,daftar *tail,daftar *node); // function yang berfungsi mencetak daftar pembelian berdasarkan booking id

void printKaryawan (tree *node); // function yang berfungsi mencetak daftar karyawan

void swap(daftar *i, daftar *j); // function yang berfungsi melakukan pertukaran data saat sorting

void sort(daftar *head, daftar *tail, daftar *node, int mode); // function yang berfungsi melakukan sorting

int printlinked2(daftar *head,daftar *tail,daftar *node); // fungsi untuk menampilkan daftar antrian

void gantifilm(jadwal *q); // fungsi untuk mengganti film.

void printtiket(spemb *headque, spemb *tailque); // fungsi untuk mencetak tiket.

int main()
{
	daftar *head,*tail,*node;

	struct jadwal q[5],dft[5];
	tree *off, *now;
    off=now=NULL;
	char ulang; // variabel untuk kembali ke menu awal
	char balik; // variabel untuk kembali ke menu customer
	int input,pilih,i,n,up;
	int pilihan;
	char password[20] = {"cineplek"};
	ulang : // label menuju menu awal
	cetakgambar(); //memanggil fungsi cetak banner cineplex.
	printf("1. Customer\n");
	printf("2. Admin\n");
	printf("0. Exit\n");
	printf("Choose : "); scanf("%d",&pilih); //meminta user memasukkan pilihan.
	if(pilih == 1) // Mode Customer
	{
		do
		{
			balik : // label menuju menu customer
			cetakgambar();
			printf("1.Pemesanan Tiket\n");
			printf("2.Pembayaran Tiket\n");
			printf("3.Pembatalan Pemesanan Tiket\n");
			printf("0.Exit\n");
			printf("Pilihan : ");
			scanf("%d",&input); //meminta user memasukkan input nomor pilihan.
			switch(input)
			{
				case 1 :
					menupembelian(head, tail); //memanggil fungsi menupembelian
					goto balik; // kembali ke menu customer
				case 2 :
					pembayaran(head,tail,node); //memanggil fungsi pembayaran
					goto balik; // kembali ke menu customer
				case 3 :
					pembatalan(head,tail); //memanggil fungsi pembatalan
					goto balik; // kembali ke menu customer
				case 0 :
					goto ulang; // kembali ke menu awal
					return 0;
			}
		}while(1);
	}
	else if (pilih == 2) // mode Admin
	{
		
		int tes = 1;
		do
		{
			char lagi; // variabel untuk kembali ke menu admin
			char pass[20];
			printf("\nAttempt %d (max = 3 attempt)\n",tes); // percobaan password
			printf("Masukkan password :"); scanf("%s",pass); // penginputan password
			if(strcmp(pass,password)==0) //mengecek ketepatan password.
			{
				lagi :; // label menuju menu admin
				cetakgambar();
				printf("1. Daftar Antrian\n");
				printf("2. Daftar Pembelian\n");
				printf("3. Daftar Film\n");
				printf("4. Daftar Karyawan\n");
				printf("5. Ganti Film\n");
				printf("0. Exit\n");
				printf("Pilihan : "); scanf("%d",&pilihan); //meminta user memasukkan input nomor pilihan.
				if(pilihan==1)
				{
					cetakgambar();
					printlinked2(head, tail, node);		
				}
				else if(pilihan==2) // daftar pembelian
				{	
					do
					{
						cetakgambar();
						printf("Tampilkan daftar pembelian berdasarkan :\n");
						printf("1. Booking ID \n");
						printf("2. Nama \n");
						printf("3. Film \n");
						printf("4. Exit \n");
						printf("Pilihan : \n");
						scanf(" %d",&up); //meminta user memasukkan input nomor sorting yang dipilih.
						if(up==1)
						{
							printlinked1(head,tail,node); //memanggil fungsi printliked1 untuk mencetak sorting booking id.	
							getch();
						}
						sort(head,tail,node,up); // sorting data berdasarkan nama dan film
					}
					while(up != 4);	
				}
				else if(pilihan==3) // daftar film
				{
					cetakgambar();
					printf("=============DAFTAR FILM=============\n");
					printfilm(head,tail);
					printf("Press any key to continue...");
					getch();

				}		
				else if(pilihan==4) // daftar karyawan
				{
					tree *root = NULL, coba[10];
					int d = 0;
					FILE *op4 = fopen("daftarkerja.txt","r");
					while(!feof(op4))
					{
						fscanf(op4,"%d#%[^#]#%s\n",&coba[d].code,coba[d].nama,coba[d].jabatan);
						if(d==0)
						{
							root = insert(root,coba,d);
						}			
						else
						{
							insert(root,coba,d);
						}		
					d++;
					}
					cetakgambar();
					printKaryawan(root); printf("\n");
					system("pause");

				}
				else if(pilihan == 5)
				{
					cetakgambar();
					gantifilm(q);
					printf("Film berhasil diganti !\n");
					printf("Press any key to continue...\n");
					getch();
				}
				else
				{
					goto ulang; // untuk kembali ke menu awal
				}
				goto lagi;	// untuk kembali ke menu admin
			}
			else
			{
				printf("\nSilahkan coba lagi\n");
				tes++;
			}
		}while(tes<=3); // untuk pengecekan password apabila lebih dari 3x kesalahan maka akan exit dari program
	} 
	else if (pilih == 0) //pilihan untuk exit.
	{ 
		exit(0);
	}
	else 
	{
		printf("Please input the correct number\nPress any key to continue...");
		getch();
		goto ulang;	// kembali ke menu awal
	}
	return 0;
}

int isEmpty (spemb *queue)
{
	// Cek apakah Stack memiliki isi.
	if(queue==NULL) return 1; // jika queue kosong
	return 0;
}

void enqueue(spemb **headque, spemb **tailque,  spemb *pt) //menambahkan data pemesanan kedalam antrian.
{
	spemb *data = (spemb*)malloc(sizeof(spemb));
	// copy data
	strcpy(data->bookid, pt->bookid);
	strcpy(data->nama, pt->nama);
	strcpy(data->film, pt->film);
	strcpy(data->jam, pt->jam);
	data->seat = pt->seat;
	strcpy(data->studio, pt->studio);
	data->next = NULL;
	
	if(isEmpty(*headque)) *headque = data;
	else (*tailque)->next = data;
	*tailque = data;
	 // berhasil menambahkan data ke queue
}

void dequeue (spemb **headque)// menghapus data pemesanan dari daftar antrian
{
	if(isEmpty(*headque)) // mengecek queue sudah kosong/belum
	{
		printf("Nothing to dequeue. Queue already empty\n");
		return;
	}
	//trash untuk menampung data yang akan dihapus
	spemb *trash = *headque;
	*headque = trash->next;
	free(trash);
	
}

spemb *front(spemb *queue){ //data antrian paling pertama.
	if (queue == NULL) return NULL;
	return queue;
}

void search(daftar *head, daftar *tail, daftar *node,char *cadfilm,char *cadjam,int takenseat[96]) //mengecek ketersediaan kursi
{
	int k=0,n=0, *bil;
	char film[30];
	int index;
	int seat[96];
	int cek;
	int taken;
    daftar *curNode; // membuat link list baru untuk di compare
	curNode = head;
	int i=0;
	strcpy(film, cadfilm); //mengcopy data cadfilm ke dalam variabel
    while (curNode != NULL)
    {
    	if(strcmp(curNode->film,film)==0 && strcmp(curNode->jam,cadjam)==0) //mengecek adanya kursi yang terisi dari setiap film yang dipilih.	
		{ 	
				takenseat[curNode->seat]=curNode->seat;
		}
    curNode = curNode->next;
	}
	for(index=1;index<=96;index++) //mengisi data seat.
    {
        seat[index] = index; 
    }
    	cetakgambar(); //memanggil fungsi cetak banner cineplex
        printf("================================================================================\n");
        printf("				          Screen\n");
        printf("================================================================================\n");
        for(index=1;index<=96;index++) //menampilkan seat.
        {
            if(seat[index] == takenseat[index]) //menandakan kursi sudah terisi.
            {  
                printf("    X");
            }
            else
            {
                printf("%5d",seat[index]); // Jika seat belum terisi maka akan ditampilkan nomor seat
            }
            if(index == 16 || index == 32 || index == 48|| index == 64|| index == 80 ) 
            {
                printf("\n");
            }
        }	

}

void printtiket(spemb *headque, spemb *tailque) // fungsi untuk print tiket yang dipesan
{   
	system("cls");
	printf("================================================\n");
	printf("                   Ticket\n");
	printf("================================================\n");
	printf("Nama     : %s\n", front(headque)->nama);
	printf("Film     : %s\n", front(headque)->film);
	printf("Pukul    : %s\n", front(headque)->jam);
	printf("Seat     : %d\n", front(headque)->seat);
	printf("Studio   : %s\n", front(headque)->studio);
	system("pause");
}

void cetakgambar() // mencetak banner gambar cineplex.
{
	system("cls");
	printf("===========================================================================================\n");
	printf("  ________     _    __      _    _______    ________    _           _______    _      _    \n ");
	printf("| _______|   | |  |  \\    | |  |  _____|  |   __   |  | |         |  _____|  \\ \\    / /   \n");
	printf(" | |          | |  |   \\   | |  | |        |  |  |  |  | |         | |         \\ \\  / /    \n");
	printf(" | |          | |  | |\\ \\  | |  | |_____   |  |__|  |  | |         | |_____     \\ \\/ /     \n");
	printf(" | |          | |  | | \\ \\ | |  |  _____|  |  ______|  | |         |  _____|     >  <      \n");
	printf(" | |          | |  | |  \\ \\| |  | |        | |         | |         | |          / /\\ \\   \n");
	printf(" | |______    | |  | |   \\   |  | |_____   | |         | |______   | |_____    / /  \\ \\    \n");
	printf(" |________|   |_|  |_|    \\__|  |_______|  |_|         |________|  |_______|  /_/    \\_\\  \n\n");
	printf("===========================================================================================\n");
}
	
void printlinked1(daftar *head,daftar *tail,daftar *node) // fungsi untuk mencetak seluruh pembelian tiket.
{ 
	daftar *temp;
	head = tail =NULL;
	FILE *fin = fopen("daftarpembelian.txt","r+"); //membuka file daftarpembelian.txt
	while (!feof(fin))
	{
		node = (daftar*)malloc(sizeof(daftar)); //membuat node untuk menampung data linklist
		fscanf(fin,"%[^#]#%[^#]#%[^#]#%[^#]#%d#%s\n",node->bookid,node->nama,node->film,node->jam,&node->seat,node->studio);//membaca data dari file daftarpembelian.txt
		if(head == NULL) //memasukkan data ke dalam linkedlist
		{
			node->prev = NULL;
			head = node;
			tail = node;
			tail->next = NULL;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = NULL;
		}
	}
	fclose(fin);
	temp = head;
	int i=1;
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("| No | Book ID |             Nama             |             FILM             |  JAM  |  SEAT  |  STUDIO  |\n");
	printf("----------------------------------------------------------------------------------------------------------\n");
	while(temp != NULL) //mencetak data dari linkedlist
	{
		printf ("|%-4d",i);
		//Pengecekan i untuk penambahan kode 0 pada booking id
		if(i<10) 
		{
	    	printf("|000%-6d",i);	
		} 
		else if(i>=10 && i<100)
		{
			printf("|00%-7d",i);
		}
		else if(i>=100 && i<1000)
		{
			printf("|0%-8d",i);
		}
		else
		{
			printf("|%-9d",i);
		}
		printf ("|%-30s",temp->nama);
		printf ("|%-30s",temp->film);
		printf ("|%-7s",temp->jam);
		printf ("|%-8d",temp->seat);
		printf ("|%-10s|\n",temp->studio);
		printf("----------------------------------------------------------------------------------------------------------\n");
		temp=temp->next;
		i++;
	}
	printf("Press any key to continue...\n");
} 

int printlinked2(daftar *head,daftar *tail,daftar *node) //fungsi untuk mencetak daftar antrian pembelian.
{ 
	daftar *temp; // Membuat link list baru untuk melakukan print
	head = tail = node = NULL;
	FILE *fop5 = fopen("daftarantri.txt","r"); //membuka data dari file daftarantri.txt
	while (!feof(fop5))
	{
		node = (daftar*)malloc(sizeof(daftar)); //membuat node untuk menampung data linklist
		fscanf(fop5,"%[^#]#%[^#]#%[^#]#%d#%s\n",node->nama,node->film,node->jam,&node->seat,node->studio);// membaca data dari file daftarantri.txt
		if(head == NULL) //memasukkan data ke dalam linkedlist
		{
			node->prev = NULL;
			head = node;
			tail = node;
			tail->next = NULL;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = NULL;
		}
	}
	fclose(fop5);
	temp = head;
	int i=1;
	
	printf("------------------------------------------------------------------------------------------------\n");
	printf("| No |             Nama             |             FILM             |  JAM  |  SEAT  |  STUDIO  |\n");
	printf("------------------------------------------------------------------------------------------------\n");
	
	while(temp != NULL) //mencetak data dari linkedlist
	{
		printf ("|%-4d",i);
		printf ("|%-30s",temp->nama);
		printf ("|%-30s",temp->film);
		printf ("|%-7s",temp->jam);
		printf ("|%-8d",temp->seat);
		printf ("|%-10s|\n",temp->studio);
		printf("------------------------------------------------------------------------------------------------\n");		
		temp=temp->next;
		i++;
	}
	printf("Press any key to continue...\n"); 
	getch();
}

void pembayaran(daftar *head, daftar *tail, daftar *node) //fungsi untuk menu pembayaran
{ 
    int choosex; int harga = 35000; int uang, kembalian; int nohp, i=0;
    cetakgambar();
    spemb *headqueue, *tailqueue,*pt, baca[1000]; // link list untuk queue 
    char nama[30];
    
    printf("Masukkan Nama	: "); scanf(" %[^\n]",nama); //meminta input nama dari user
    
	headqueue = tailqueue = NULL;
	FILE *ip = fopen("daftarantri.txt","r+"); //membuka file daftarantri.txt
	while (!feof(ip))
	{
		pt = (spemb*)malloc(sizeof(spemb));
		fscanf(ip,"%[^#]#%[^#]#%[^#]#%d#%s\n",pt->nama,pt->film,pt->jam,&pt->seat,pt->studio); // membaca data dari file daftarantri.txt
		enqueue(&headqueue,&tailqueue,pt); // memanggil fungsi enqueue untuk menambahkan daftar antrian
	}
	fclose(ip);
	if (strcmp(front(headqueue)->nama,nama)==0)
	{
	    printf("PEMBAYARAN TIKET\n\n");
	    printf("Metode Pembayaran\n");printf("1. OXO\n2. Ga-Pay\n3. Cash\nChoose: \n");
	    scanf("%d", &choosex); //meminta input user memilih jenis pembayaran
	    switch (choosex)
		{
	        case 1 : //menu pembayaran menggunakan OXO
	            printf("Nominal Yang Harus Dibayar : Rp. %d\n", harga);
	            printf("Masukkan Nomor Handphone : \n"); scanf("%d", &nohp); //meminta user memasukkan input jumlah uang
	            printf("Pembayaran Berhasil Melalui OXO\n");break;
	
	        case 2 : // menu pembayaran menggunakan Ga-Pay
	            printf("Nominal Yang Harus Dibayar : Rp. %d\n", harga);
	            printf("Masukkan Nomor Handphone : \n"); scanf("%d", &nohp); //meminta user memasukkan input jumlah uang
	            printf("Pembayaran Berhasil Melalui Ga-Pay\n");break;
	
	        case 3 : // menu pembayaran menggunakan Cash.
	            printf("Nominal Yang Harus Dibayar : Rp. %d\n", harga);
	            printf("Nominal Uang Yang Diterima : \n"); scanf("%d", &uang); //meminta user memasukkan input jumlah uang
	            if(uang>harga)
				{
	           	 	kembalian = uang - harga;
	            	printf("Nominal Kembalian : %d\n", kembalian);
	            	printf("Terima Kasih\n");
				}
	            else if(uang == harga)
				{
	            	printf("Terima Kasih\n");
	            }break;
	    }
		i++;
		int x = 0;
		FILE *op3 = fopen("daftarpembelian.txt","r"); //membaca data pembelian dari file daftarpembelian.txt
		while(!feof(op3))
		{
			fscanf(op3,"%d#%[^#]#%[^#]#%[^#]#%d#%s\n",&baca[i].bookid,baca[i].nama,baca[i].film,baca[i].jam,&baca[i].seat,baca[i].studio);
			i++;
			x++;
		}
		fclose(op3);
		
		FILE *prit = fopen("daftarpembelian.txt","a+"); // memasukkan data pembelian ke dalam file daftarpembelian.txt
		fprintf(prit,"%d#%s#%s#%s#%d#%s\n",x+1,front(headqueue)->nama,front(headqueue)->film,front(headqueue)->jam,front(headqueue)->seat,front(headqueue)->studio);
		fclose(prit);
		
		printtiket(headqueue, tailqueue); //memanggil fungsi printtiket untuk menampilkan tiket yang sudah dibeli user.
	    
		FILE *del = fopen("daftarantri.txt","w+");
	    dequeue(&headqueue); // memanggil fungsi dequeue untuk menghapus antrian pemesanan yang sudah di bayar.
	    while (front(headqueue) != NULL)
	        {
	            fprintf(del,"%s#%s#%s#%d#%s\n",front(headqueue)->nama,front(headqueue)->film,front(headqueue)->jam,front(headqueue)->seat,front(headqueue)->studio);
	            dequeue(&headqueue);//menghapus antrian pemesanan yang sudah di bayar.
	        }
		fclose(del);
		getch();
	    
	}
	else
	{
		printf("Data tidak sesuai urutan\n");
		getch();
	}

}

void pembeliantiket(jadwal *q,int i) //fungsi untuk menu pembelian tiket.
{
    int input;
    int takenseat[96];
    int index,taken;
    char ulang;
    int x=0,std=0;
    char nama[50],kalimat,jam[10],yes,cadfilm[100],cadjam[10];
    struct daftar *head, *tail,*node,*tambah;
    head = tail =NULL;
	FILE *fin = fopen("daftarpembelian.txt","r+"); //membuka file daftarpembelian.txt
	while (!feof(fin))
	{
		node = (daftar*)malloc(sizeof(daftar)); //membuat node untuk menampung data linklist
		fscanf(fin,"%[^#]#%[^#]#%[^#]#%[^#]#%d#%[^\n]\n",node->bookid,node->nama,node->film,node->jam,&node->seat,node->studio);
		
		if(head == NULL) //memasukkan data ke dalam linklist
		{
			node->prev = NULL;
			head = node;
			tail = node;
			tail->next = NULL;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = NULL;
		}
		x++;
	}
	fclose(fin);
    x=x+1;
   	system("cls");
    printf("===================================================================\n");
    printf("                         Pembelian Tiket                           \n");
    printf("===================================================================\n");
    printf("Judul Film : %s\n",q[i].judul); //menampilkan judul film yang dipilih
    printf("Studio     : %s\n",q[i].studio); //menampilkan studio film yang dipilih
    printf("Nama       : "); 
    scanf("%c",&kalimat);
    scanf("%[^\n]",nama); //meminta user untuk memasukkan nama.
    printf("Jam Tayang :\n1. %s\n2. %s\n3. %s\n4. %s\n",q[i].jam,q[i].pukul,q[i].time,q[i].waktu); //menampilan jam tayang yang tersedia.
    printf("Masukkan Jam yang Dipilih : "); 
    scanf("%d",&input); //meminta user memasukkan nomor jam tayang yang ada.
    
  	strcpy(node->nama,nama);// mengcopy  nama ke dalam node
  	strcpy(cadfilm,q[i].judul);// mengcopy judul ke dalam variabel cadfilm
  	strcpy(tambah->film,q[i].judul);// mengcopy judul ke dalam variabel.
  	
	if(input==1)
	{
    	strcpy(cadjam,q[i].jam); //memindahkan waktu 1 dari struct aray ke dalam variabel
	}
	if(input==2)
	{
    	strcpy(cadjam,q[i].pukul); //memindahkan waktu 2 dari struct aray ke dalam variabel
	}
	if(input==3)
	{
    	strcpy(cadjam,q[i].time); //memindahkan waktu 3 dari struct aray ke dalam variabel
	}
	if(input==4)
	{
    	strcpy(cadjam,q[i].waktu); //memindahkan waktu 4 dari struct aray ke dalam variabel
	}
	strcpy(node->studio,q[i].studio); //memindahkan studio dari struct array ke dalam linkedlist
	
	search(head,tail,node,cadfilm,cadjam,&takenseat[96]); //memanggil fungsi search	
    printf("\nMasukkan no seat : "); scanf(" %d",&taken); //meminta user untuk memilih nomor kursi.
    takenseat[taken] = taken; // Memasukkan input seat ke array
	node->seat = taken; // Memasukkan input seat data ke linkedlist
	strcpy(node->film,q[i].judul); //memindahkan judul film dari struct array ke dalam linkedlist
	if(input==1)
	{
    	strcpy(node->jam,q[i].jam); //memindahkan waktu 1 dari struct array ke dalam linkedlist
	}
	if(input==2)
	{
    	strcpy(node->jam,q[i].pukul); //memindahkan waktu 2 dari struct array ke dalam linkedlist
	}
	if(input==3)
	{
    	strcpy(node->jam,q[i].time); //memindahkan waktu  3 dari struct array ke dalam linkedlist
	}
	if(input==4)
	{
    	strcpy(node->jam,q[i].waktu); //memindahkan waktu  4 dari struct array ke dalam linkedlist
	}

    FILE *fout = fopen("daftarantri.txt","a+");
	fprintf(fout,"%s#%s#%s#%d#%s\n",node->nama,node->film,node->jam,node->seat,node->studio); //mencetak data kedalam file daftarantrian.txt
	fclose(fout);
	printf("Pemesanan berhasil ! \n");
	printf("Press any key to continue...\n");
	getch();
}

void menupembelian(daftar *head, daftar *tail) // fungsi untuk menu pembelian tiket
{ 
	int i=0,k;
	struct jadwal q[5];
	char *bil;
	FILE *bisa = fopen("daftarfilm.txt","r");
	while (!feof(bisa))
	{
		fscanf(bisa,"%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%s\n",q[i].judul,q[i].jam,q[i].pukul,q[i].time,q[i].waktu,q[i].studio);
		i++;
	}
	fclose(bisa);
	i=0;
	while(k!=0)
	{
		cetakgambar(); //memanggil menu cetak untuk banner cineplek
		printf("===================================================================\n");
		printf("                         Menu Pemesanan Tiket                      \n");
		printf("===================================================================\n");
		printf("Judul\t\t: %s\n",q[i].judul); // menampilkan judul film yang tersedia
		printf("Jam Tayang\t: %s %s %s %s \n",q[i].jam,q[i].pukul,q[i].time,q[i].waktu); // menampilkan jam tayang dari film
		printf("Studio Film\t: %s\n\n",q[i].studio); // menampilkan studio.
		printf("1) Prev\n");
		printf("2) Next\n");
		printf("3) Pembelian Tiket\n");
		printf("0) Exit\n");
		printf("Masukkan Pilihan : "); //input user untuk memilih next, prev, atau pembelian.
		scanf("%d",&k);
		if(k==1) // fungsi jika user memilih prev
		{ 
			if(i==0)
			{	
					// Karena i merupakan index paling awal maka tidak bisa di prev 
			}
			else
			{
				i--; // untuk mengurangi index i			
			}
		}
		if(k==2) //fungsi jika user memilih next
		{ 
			if(i==4)
			{
				// Karena i merupakan index paling akhir maka tidak bisa di next
			}
			else
			{
				i++; // untuk menambahkan index i
			}
		}
		if(k==3) // fungsi untuk user memilih pembelian tiket.
		{ 
			pembeliantiket(q,i);
			break;
		}
	}
}

void printfilm(daftar *head, daftar *tail) // fungsi untuk memu cetak dafttar film
{
	int i=0;
	struct jadwal dft[5];
	char *bil;
	FILE *bisa2 = fopen("daftarfilm.txt","r");
	while (!feof(bisa2))
	{
		fscanf(bisa2,"%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%s\n",dft[i].judul,dft[i].jam,dft[i].pukul,dft[i].time,dft[i].waktu,dft[i].studio);
		i++;
	}
	fclose(bisa2);

	for(i=0;i<5;i++)
	{
		printf("%d. %s\n",i+1,dft[i].judul);
	}
} 

void pembatalan(daftar *head, daftar *tail) // fungsi untuk menu pembatalan
{
	char searchnama[30];
	char awalbatal;
	int found =0,z=0,i;
	struct daftar *node, *curr;
    head = tail =NULL;
	FILE *fin3 = fopen("daftarantri.txt","r+");
	while (!feof(fin3))
	{
		node = (daftar*)malloc(sizeof(daftar));
		fscanf(fin3,"%[^#]#%[^#]#%[^#]#%d#%s\n",node->nama,node->film,node->jam,&node->seat,node->studio);
		if(head == NULL) // Memasukan data ke linkedlist
		{
			node->prev = NULL;
			head = node;
			tail = node;
			tail->next = NULL;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = NULL;
		}
		z++;
	}
	fclose(fin3);
	awalbatal : // untuk kembali ke menu pembatalan tiket
	cetakgambar();
	printf("Masukkan nama (Lengkap) yang ingin dibatalkan : "); scanf("%s",searchnama); //meminta input user nama yang ingin dibatalkan.
	// Linear Search
	curr = head;
	char yakin; // variabel untuk mengkonfirmasi pembatalan tiket

	for(i=0;i<z;i++)
	{
		if(strcmp(searchnama,curr->nama)==0) //membandingkan nama yang ada difile dengan nama inputan user.
		{
			if (head == curr) 
			{
				head = head->next;
			}
			else if (tail == curr)
			{
				tail = tail->prev;
				tail->next = NULL;
			}
			else 
			{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;	
			}
			found = 1;
			printf("Nama   : %s\n",curr->nama);
			printf("Film   : %s\n",curr->film);
			printf("Jam    : %s\n",curr->jam);
			printf("Seat   : %d\n",curr->seat);
			printf("Studio : %s\n",curr->studio);
			printf("Apakah anda yakin untuk membatalkan tiket (Y/N) ? : "); scanf(" %c", &yakin); 
			if(yakin == 'Y' || yakin == 'y')
			{
				free(curr);
				break;
			} 
			else if (yakin == 'N' || yakin == 'n') 
			{
				printf("Tiket tidak dibatalkan\n"); getch(); 
				break;
			} 
			else 
			{
				printf("Input salah, silahkan coba lagi\n"); 
				getch();
				goto awalbatal;
			}
		}
		curr = curr->next;
	}
	if(found == 1 && yakin == 'Y')
	{
		curr = head;
		FILE *fout2 = fopen("daftarantri.txt","w"); //membuka file dari daftarantri.txt
		while(curr!=NULL)
		{
			fprintf(fout2,"%s#%s#%s#%d#%s\n",curr->nama,curr->film,curr->jam,curr->seat,curr->studio);
			curr = curr->next;
		}
		fclose(fout2);
		printf("Tiket berhasil dibatalkan !\nPress any key to continue...\n"); getch();
	}
	if (found != 1)
	{	
		printf("Data tidak ditemukan !\nPress any key to continue...\n"); getch();
	}
}

tree *newNode(int item,char nama1[30],char jab[10]) //fungsi untuk memasukkan data linklist ke dalam tree
{ 
	 tree *temp = (tree*) malloc(sizeof(tree));
	 temp->code = item;
	 strcpy(temp->nama,nama1);
	 strcpy(temp->jabatan,jab);
	 temp->left = temp->right = NULL;
	 return temp;
}


tree *insert(tree *node,tree *coba,int d)
{
 	// Jika tree kosong
 	// Atau ketika berada pada node kosong (left/right)
 	if (node == NULL)
  	return newNode (coba[d].code,coba[d].nama,coba[d].jabatan);
 	// Jika key kurang dari key pada node sementara
 	if (coba[d].code < node->code)
  	// Turun ke left dari node sementara
	node->left = insert(node->left, coba,d);
	  
	// Jika key lebih dari key pada node sementara
	else if (coba[d].code > node->code)
	// Turun ke right dari node sementara
	node->right = insert (node->right, coba,d);
	  
	// return node jika sudah berhasil insert
	return node;
}

void printKaryawan (tree *node) //fungsi untuk print daftar karyawan yang ada di tree.
{ 
	if (node == NULL) return;
	printf("%d. %-10s | %s\n", node->code,node->nama,node->jabatan);
	printKaryawan (node->right);
	printKaryawan (node->left);
}

void swap(daftar *i, daftar *j) //fungsi untuk memasukkan data ke dalam linkedlist untuk disortir.
{
    daftar *node;
    node=(daftar*) malloc(sizeof(daftar));
    //mengcopy data dari i ke node untuk melakukan swap data.
   	strcpy(node->bookid,i->bookid);  
    strcpy(node->nama,i->nama);
    strcpy(node->film,i->film);
    strcpy(node->jam,i->jam);
    strcpy(node->studio,i->studio);
    node->seat=i->seat;
    //mengcopy data dari j ke i untuk melakukan swap data.
	strcpy(i->bookid,j->bookid);
    strcpy(i->nama,j->nama);
    strcpy(i->film,j->film);
    strcpy(i->jam,j->jam);
    strcpy(i->studio,j->studio);
    i->seat=j->seat;
    //mengcopy data dari node ke j untuk melakukan swap data.
	strcpy(j->bookid,node->bookid);
    strcpy(j->nama,node->nama);
    strcpy(j->film,node->film);
    strcpy(j->jam,node->jam);
    strcpy(j->studio,node->studio);
    j->seat=node->seat;

    free(node);
}

void sort(daftar *head, daftar *tail, daftar *node, int mode)//fungsi untuk sortir linked list pesanan
{
	int i=1;
    daftar *curr,*temp;
    FILE *pr = fopen("daftarpembelian.txt","r"); //membuka file dari daftarpembelian.txt
    head=tail=NULL;
	while(!feof(pr))
	{
		node = (daftar*)malloc(sizeof(daftar));
		fscanf(pr,"%[^#]#%[^#]#%[^#]#%[^#]#%d#%s\n",node->bookid,node->nama,node->film,node->jam,&node->seat,node->studio); //membaca data dari file daftarpembelian.txt
		if(head == NULL) //memasukkan data ke dalam linkedlist.
		{
			node->prev = NULL;
			head = node;
			tail = node;
			tail->next = NULL;
		}
		else
		{
			tail->next = node;
			node->prev = tail;
			tail = node;
			tail->next = NULL;
		}
	}
	fclose(pr);
    if(head ==NULL)//error cek sederhana
    {
        printf("Tidak ada data yang dapat disortir");
        return;
    }

    curr= head;
    //selection sort
    if(mode==2)//sortir berdasarkan nama
    {
        while(curr->next!=NULL)
        {
            node=curr->next;
            while(node!=NULL)
            {
                if(strcmp(curr->nama,node->nama)>0)//melakukan swap data pada linked list
                    swap(curr, node);
                node=node->next;
            }
            curr=curr->next;
        }
	    temp = head;
	    printf("----------------------------------------------------------------------------------------------------------\n");
		printf("| No | Book ID |             Nama             |             FILM             |  JAM  |  SEAT  |  STUDIO  |\n");
		printf("----------------------------------------------------------------------------------------------------------\n");
	    while(temp != NULL) //mencetak data dari linkedlist.
		{ 
	        printf ("|%-4d",i);
	        printf ("|%-9s",temp->bookid);
			printf ("|%-30s",temp->nama);
			printf ("|%-30s",temp->film);
			printf ("|%-7s",temp->jam);
			printf ("|%-8d",temp->seat);
			printf ("|%-10s|\n",temp->studio);
			printf("----------------------------------------------------------------------------------------------------------\n");
	        temp=temp->next;
	        i++;
		}
		printf("Press any key to continue...\n"); getch();
    }
	if(mode==3)//sortir berdasarkan film
    {
        while(curr->next!=NULL)
        {
            node=curr->next;
            while(node!=NULL)
            {
                if(strcmp(curr->film,node->film)>0)//melakukan swap data pada linked list
                swap(curr, node);
                node=node->next;
            }
            curr=curr->next;
        }
        temp = head;
        i=1;
	    printf("----------------------------------------------------------------------------------------------------------\n");
		printf("| No | Book ID |             Nama             |             FILM             |  JAM  |  SEAT  |  STUDIO  |\n");
		printf("----------------------------------------------------------------------------------------------------------\n");
        while(temp != NULL) //mencetak data dari linkedlist
		{ 
	        printf ("|%-4d",i);
	        printf ("|%-9s",temp->bookid);
			printf ("|%-30s",temp->nama);
			printf ("|%-30s",temp->film);
			printf ("|%-7s",temp->jam);
			printf ("|%-8d",temp->seat);
			printf ("|%-10s|\n",temp->studio);
			printf("----------------------------------------------------------------------------------------------------------\n");
	        temp=temp->next;
	        i++;
		}
		printf("Press any key to continue...\n"); getch();
	}
}

void gantifilm(jadwal *q) // fungsi untuk menu ganti film
{ 
	int i=0, j, pil;
	char judul[30];
	FILE *fop6 = fopen("daftarfilm.txt","r"); //membuka file daftarfilm.txt
	while (!feof(fop6))
	{
		fscanf(fop6,"%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%s\n",q[i].judul,q[i].jam,q[i].pukul,q[i].time,q[i].waktu,q[i].studio); //membaca data dari file daftarfilm.txt
		i++;
	}
	fclose(fop6);
	
	printf("Daftar Film\n");
	for(j = 0; j < i; j++)
	{
		printf("%d. %s\n", j+1, q[j].judul);
	}
	printf("Film Yang Akan Diganti : "); scanf(" %d", &pil); //meminta user memasukkan nomor film yang ingin diganti 
	printf("Judul Film yang Baru : "); scanf(" %[^\n]", judul); //meminta user memasukkan nama film yang baru
	strcpy(q[pil-1].judul, judul);
	
	FILE *fcut = fopen("daftarfilm.txt","w+"); //membuka file daftarfilm.txt
	for(j=0; j<i; j++)
	{
		fprintf(fcut,"%s#%s#%s#%s#%s#%s\n",q[j].judul,q[j].jam,q[j].pukul,q[j].time,q[j].waktu,q[j].studio); //memasukkan data ke dalam file daftarfilm.txt
	}
	fclose(fcut);
}

