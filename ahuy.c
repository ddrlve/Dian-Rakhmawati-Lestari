#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Definisi struct untuk Player
struct Player {
    char nama[50];
    int skor;
};

// Fungsi untuk menambah skor pemain ke file
void tambahSkorKeFile(const char *filename, struct Player p) {
    FILE *file = fopen(filename, "a");  // Mode "a" untuk menambah data
    if (file != NULL) {
        fprintf(file, "Nama: %s, Skor: %d\n", p.nama, p.skor);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menambah skor!\n");
    }
}

int muatScoreboardDariFile(const char *filename, struct Player players[]) {
    FILE *file = fopen(filename, "r");
    int count = 0;

    if (file != NULL) {
        while (fscanf(file, "Nama: %49[^,], Skor: %d\n", players[count].nama, &players[count].skor) == 2) {
            count++;
        }
        fclose(file);
    } else {
        printf("Gagal membuka file scoreboard!\n");
    }
    
    return count;  // Mengembalikan jumlah pemain yang dimuat
}

// Fungsi untuk sorting skor pemain menggunakan bubble sort
void bubbleSort(struct Player arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].skor < arr[j+1].skor) {
                struct Player temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void tampilkanScoreboard(struct Player arr[], int n) {
    printf("\n===== SCOREBOARD =====\n");
    printf("| %-30s | %-5s |\n", "Nama Pemain", "Skor");
    printf("|--------------------------------|-------|\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %-30s | %-5d |\n", arr[i].nama, arr[i].skor);
    }
    printf("\n");
}

void hapusPemain(const char *filename, struct Player players[], int *playerCount) {
    char nama[50];
    printf("Masukkan nama pemain yang ingin dihapus: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0;  // Menghapus newline
    printf("Nama yang dicari: '%s'\n", nama); // Debug statement

    int i, j;
    for (i = 0; i < *playerCount; i++) {
        if (strcmp(players[i].nama, nama) == 0) {
            for (j = i; j < *playerCount - 1; j++) {
                players[j] = players[j + 1];
            }
            (*playerCount)--; // Mengurangi jumlah pemain
            printf("Pemain %s telah dihapus dari scoreboard.\n", nama);
            break;
        }
    }

    if (i == *playerCount) {
        printf("Pemain dengan nama %s tidak ditemukan.\n", nama);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (i = 0; i < *playerCount; i++) {
            fprintf(file, "Nama: %s, Skor: %d\n", players[i].nama, players[i].skor);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data!\n");
    }
}
//void removeAccount(const char *filename) {
//    char nama[50];
//    printf("Masukkan nama akun yang ingin dihapus: ");
//    fgets(nama, sizeof(nama), stdin);
//    nama[strcspn(nama, "\n")] = '\0'; // Menghapus newline dari input
//
//    // Nama file sementara
//    const char *tempFilename = "temp.txt";
//    FILE *file = fopen(filename, "r");
//    FILE *tempFile = fopen(tempFilename, "w");
//    bool accountFound = false;
//
//    if (file == NULL || tempFile == NULL) {
//        printf("Gagal membuka file!\n");
//        if (file != NULL) fclose(file);
//        if (tempFile != NULL) fclose(tempFile);
//        return;
//    }
//
//    char line[100];
//    while (fgets(line, sizeof(line), file) != NULL) {
//        char currentName[50];
//        int score;
//        // Parsing data dari baris file
//        if (sscanf(line, "Nama: %49[^,], Skor: %d", currentName, &score) == 2) {
//            if (strcmp(currentName, nama) == 0) {
//                accountFound = true; // Akun ditemukan
//            } else {
//                fprintf(tempFile, "Nama: %s, Skor: %d\n", currentName, score); // Salin data ke file sementara
//            }
//        }
//    }
//
//    fclose(file);
//    fclose(tempFile);
//
//    if (accountFound) {
//        // Menghapus file asli dan mengganti dengan file sementara
//        if (remove(filename) == 0 && rename(tempFilename, filename) == 0) {
//            printf("Akun '%s' berhasil dihapus.\n", nama);
//        } else {
//            printf("Gagal mengganti file!\n");
//        }
//    } else {
//        printf("Akun dengan nama '%s' tidak ditemukan.\n", nama);
//        remove(tempFilename); // Hapus file sementara jika tidak digunakan
//    }
//}


 //Fungsi untuk menambahkan pemain ke dalam array
void tambahPemainKeArray(struct Player arr[], int *n, char *nama, int skor) {
    struct Player newPlayer;
    strcpy(newPlayer.nama, nama);
    newPlayer.skor = skor;
    arr[*n] = newPlayer;
    (*n)++;
}

//// Fungsi untuk menu utama scoreboard
//void menuScoreboard() {
//    struct Player players[100];
//    int playerCount = 0;
//    char filename[] = "scoreboard.txt";
//    
//    // Memuat data dari file saat pertama kali menjalankan
//    playerCount = muatScoreboardDariFile(filename, players);	    
//
//    while (1) {
//        printf("\n==== Menu Scoreboard ====\n");
//        printf("1. Tambah Skor\n");
//        printf("2. Tampilkan Scoreboard\n");
//        printf("3. Exit\n");
//        printf("Pilih menu: ");
//        
//        int choice;
//        scanf("%d", &choice);
//        getchar();  // Mengkonsumsi newline
//
//        switch (choice) {
//            case 1: {
//            	system("cls");            	
//                char nama[50];
//                int skor;
//                printf("Masukkan Nama Pemain: ");
//                fgets(nama, sizeof(nama), stdin);
//                nama[strcspn(nama, "\n")] = 0;  // Menghapus newline
//                printf("Masukkan Skor Pemain: ");
//                scanf("%d", &skor);
//                
//                // Menambahkan skor ke file dan array
//                struct Player p = {0};
//                strcpy(p.nama, nama);
//                p.skor = skor;
//                tambahSkorKeFile(filename, p);
//                tambahPemainKeArray(players, &playerCount, nama, skor);
//                break;
//            }
//            case 2:
//            	system("cls");            	
//                bubbleSort(players, playerCount);  // Mengurutkan array skor pemain
//                tampilkanScoreboard(players, playerCount); // Menampilkan scoreboard yang sudah disort
//                break;
//            case 3:
//            	system("cls");            	
//                printf("Keluar dari menu scoreboard.\n");
//                return;  // Keluar dari fungsi menu scoreboard
//            default:
//            	system("cls");            	
//                printf("Pilihan tidak valid! Coba lagi.\n");
//        }
//    }
//}

/* {====================== All About Musim ======================} */
// Enum musim
enum musim {
  	SEMI,
  	GUGUR,
  	DINGIN,
  	PANAS,
    TOTAL_MUSIM // Ngitung total musim
};

// Fungsi untuk dapet musim acak
enum musim randomMusims() {
    return rand() % TOTAL_MUSIM; // Mengambil angka acak dari index 0 sampai (TOTAL_MUSIM - 1)
}
/* {=============================================================} */



/* {====================== All About Tanaman ======================} */
// Data tanaman
char namaTanaman[10][10] = {"Brokoli", "Tomat", "Bayam", "Timun", "Buncis", "Selada", "Bawang", "Seledri", "Terong", "Sawi"}; 
int idTanaman[10] = {1,2,3,4,5,6,7,8,9,10}; 
char tanamanAwal[10];
	
// Fungsi milih tanaman acak ketika mulai (AWAL)
int tanamanAcak(int *idTanamanAwal){
	srand(time(NULL));
	int randomTaneman = rand() % 10 + 1; // random 1 - 10
	for (int i = 0; i < 10; i++) { // ngitung dari 1 - 10
    if (idTanaman[i] == randomTaneman) { // kalau hitungan adalah sama dengan id hasil random 1-10
    	*idTanamanAwal = i; // maka id tanaman akan di set ke hasil hitung
    	break; 
    	}
	}
}

// Fungsi random kondisi AWAL air tanaman
int airTanamanRandom(int *airTanaman){
	*airTanaman = rand() % 11; *airTanaman += 40; // ini artinya random 1-10 dan akan di tambah 40
}

// Fungsi random pengurangan air tanaman (Seiring berjalannya hari)
int penguranganAirRandom(int *penguranganAirRandom, enum musim m) {
	int penguranganAir;
	switch (m) {
        case SEMI:
        	penguranganAir = rand() % 11; penguranganAir += 10;	
			*penguranganAirRandom -= penguranganAir;
        break;
        case GUGUR:
            penguranganAir = rand() % 11; penguranganAir += 10;	
			*penguranganAirRandom -= penguranganAir;
        break;
        case DINGIN:
            penguranganAir = rand() % 11; penguranganAir += 10;	
			*penguranganAirRandom -= penguranganAir;;
        break;
        case PANAS:
        	penguranganAir = rand() % 11; penguranganAir += 20; // 20 karena efek musim	
			*penguranganAirRandom -= penguranganAir;
        break;
    }
}

// Fungsi random nyiram tanaman
int fungsiNyiramTanaman(int *fungsiNyiramTanaman, enum musim m) {
	int beku = rand() % 11;
	int menguap = rand() % 11;
	int nyiramRandom;
	switch (m) {
		case SEMI:
			nyiramRandom = rand() % 11 + 30 - 10;
			*fungsiNyiramTanaman += nyiramRandom;
		break;
		case GUGUR:
			nyiramRandom = rand() % 11 + 30 - 10;
			*fungsiNyiramTanaman += nyiramRandom;
		break;
        case DINGIN:
        	// Kemungkinan air membeku sangat kecil, kalau beku, maka tdk ada air yg diberikan pada tanaman
        	if (beku == 5) { 
        		break;
			} 
            nyiramRandom = rand() % 11 + 30;
			*fungsiNyiramTanaman += nyiramRandom;
        break;
        case PANAS:
        	// Kemungkinan air menguap sangat kecil, kalau menguap, air hanya ber efek setengahnya
        	if (menguap == 5) {
        		int nyiramRandom = (rand() % 11 + 30)/2;
				*fungsiNyiramTanaman += nyiramRandom;
			}
			// Kalau normal maka air -10 karena musim panas
			else if (menguap != 5){
				nyiramRandom = rand() % 11 + 30 - 10;
				*fungsiNyiramTanaman += nyiramRandom;
			}
        break;
    }
}

// Fungsi random kondisi AWAL pertumbuhan tanaman
int pertumbuhanTanamanRandom(int *pertumbuhanTanaman){
	*pertumbuhanTanaman = rand() %11; pertumbuhanTanaman += 10; // ini artinya random 1-10 lalu ditambahkan 10
}

// Fungsi random tanaman tumbuh (Seiring berjalannya hari)
int pertambahanPertumbuhanRandom(int *pertambahanPertumbuhanRandom, enum musim m) {
	int pertambahanPertumbuhan;
	switch (m) {
        case SEMI:
        	pertambahanPertumbuhan = rand() % 6 + 10 + 10; // +10 yg belakang adalah bonus musim
			*pertambahanPertumbuhanRandom += pertambahanPertumbuhan;
        break;
        case GUGUR:
            pertambahanPertumbuhan = rand() % 6 + 10 - 10; // -10 adalah efek musim
			*pertambahanPertumbuhanRandom += pertambahanPertumbuhan;
        break;
        case DINGIN:
            pertambahanPertumbuhan = rand() % 6 + 10 - 5; // -5 adalah efek musim
			*pertambahanPertumbuhanRandom += pertambahanPertumbuhan;
        break;
        case PANAS:
        	pertambahanPertumbuhan = rand() % 6 + 10 - 5; // -5 adalah efek musim
			*pertambahanPertumbuhanRandom += pertambahanPertumbuhan;
        break;
    }
}

// Fungsi random mupuk tanaman
int fungsiMupukTanaman(int *fungsiMupukTanaman, enum musim m) {
		int mupukRandom;
	switch (m) {
        case SEMI:
			mupukRandom = rand() % 11 + 10; // + 10 adlh efek musim
			*fungsiMupukTanaman += mupukRandom;
        break;
        case GUGUR:
            mupukRandom = rand() % 11 - 10; // - 10 adlh efek musim
			*fungsiMupukTanaman += mupukRandom;
        break;
        case DINGIN:
           	mupukRandom = rand() % 11 - 5; // - 5 adlh efek musim
			*fungsiMupukTanaman += mupukRandom;
        break;
        case PANAS:
        	mupukRandom = rand() % 11 - 5; // - 5 adlh efek musim
			*fungsiMupukTanaman += mupukRandom;
        break;
    }
}
/* {===============================================================} */



char nama[11];
bool keluar;



// Menu awal
void menuMulai(){

	bool enterNickCondition = true;
	
	while(enterNickCondition){
		puts("+-----------------------+");
		puts("\tPlanTra");
		puts("+-----------------------+");
		puts("");
		puts("Selamat datang di PlanTra.");
		puts("Silahkan masukan nama anda [Maks 10 karakter]:");
		printf(">> ");
		scanf("%[^\n]", &nama); getchar();
		
		if (strlen(nama) > 10){
			system("cls");
			puts("\033[0;31mMaaf input anda tidak valid. [Maks 10 karakter]");
			printf("\033[0m");
		}
		else if(strlen(nama) <= 0){
			system("cls");
			puts("\033[0;31mMaaf input tidak boleh kosong.");
			printf("\033[0m");
		}else{
			enterNickCondition = false;
			system("cls");
		}
	}
}



int settingHari(int *ptrHari){
	*ptrHari = 1;
}

// Menu permainan
void menuMain(){
	
	puts("Kamu akan diberikan satu tanaman acak untuk memulai.");
	puts("Ketuk 'Enter' untuk benar - benar memulai.");
	getchar();
	system("cls");
	
	// Memanggil enum musim & fungsi random musim
	enum musim randomMusim = randomMusims();

	// Memanggil dari fungsi settingHari, mengatur hari agar setiap mulai 1, dan bisa di hari++
	int hari;
	int *ptrHari = &hari;
	settingHari(ptrHari);
	
	// Memanggil fungsi tanamanAcak (Gacha taneman yang akan diberikan di awal)
	int idTanamanAcak;
	int *ptrIdTanamanAcak = &idTanamanAcak;
	tanamanAcak(ptrIdTanamanAcak);
	
	// Dari hasil random tanamanAcak, bakalan dapet apa
	for (int i = 0; i < 10; i++) {
    	if (idTanaman[i] == idTanamanAcak) {
    	strcpy(tanamanAwal, namaTanaman[i]);
    	break;
		}
	}
	
	// Kondisi air tanaman (random)
	int airTanaman;
	int *ptrAirTanaman = &airTanaman;
	airTanamanRandom(ptrAirTanaman);
	
	// Kondisi pertumbuhan tanaman (random)
	int pertumbuhanTanaman;
	int *ptrPertumbuhanTanaman = &pertumbuhanTanaman;
	pertumbuhanTanamanRandom(ptrPertumbuhanTanaman);

	bool kondisiPermainan = true;
	int skor = 0; // Inisialisasi skor
	bool masihBisaNgerawat = true;
	
	while(kondisiPermainan){
	
		if (hari > 7) {
			puts("=============================");
			puts("\tTAMAT KOCAK");
			puts("=============================");
			printf("Total hari: %d\n", hari-1);
			kondisiPermainan = false;
			puts("Ketuk 'Enter' untuk kembali ke menu utama.");
			getchar();
			break;

		}
		else if (hari == 1){
			switch (randomMusim) {
        		case SEMI:
        			printf("----|Hari: %d \tMusim: Semi|----\n", hari);
        			puts("(+10% Pertumbuhan)");
            	break;
        		case GUGUR:
            		printf("----|Hari: %d \tMusim: Gugur|----\n", hari);
            		puts("(-10% Pertumbuhan)");
           	 	break;
        		case DINGIN:
            		printf("----|Hari: %d \tMusim: Dingin|----\n", hari);
            		puts("(-5% Pertumbuhan ; Air bisa membeku)");
         	   	break;
        		case PANAS:
        	    	printf("----|Hari: %d \tMusim: Panas|----\n", hari);
        	    	puts("(-5% Pertumbuhan ; -10 Air Penyiraman ; Air bisa menguap ; Tanaman lebih haus)");
            	break;
    		}
			puts("===================================================");
			puts("");
			printf("Selamat datang [%s]\n", nama);
			printf("Karena ini adalah hari pertamamu, kami berikan kamu tanaman [%s].\n\n", tanamanAwal);
			printf("|Taneman 1\t: %-14s|\n", tanamanAwal);
			printf("|Dehidrasi\t: %d%%\t\t|\n", airTanaman);
			printf("|Pertumbuhan\t: %d%%\t\t|\n", pertumbuhanTanaman); 
		}
		else if (hari > 1){
			if (airTanaman <= 0) {
				system("cls");
				printf("Tanaman anda mati, permainan berakhir\n");
				skor = 0; //jika mati
				masihBisaNgerawat = false;
				kondisiPermainan = false;
			}else {
				switch (randomMusim) {
        		case SEMI:
        			printf("----|Hari: %d \tMusim: Semi|----\n", hari);
        			puts("(+10% Pertumbuhan)");
            	break;
        		case GUGUR:
            		printf("----|Hari: %d \tMusim: Gugur|----\n", hari);
            		puts("(-10% Pertumbuhan)");
           	 	break;
        		case DINGIN:
            		printf("----|Hari: %d \tMusim: Dingin|----\n", hari);
            		puts("(-5% Pertumbuhan ; Air bisa membeku)");
         	   	break;
        		case PANAS:
        	    	printf("----|Hari: %d \tMusim: Panas|----\n", hari);
        	    	puts("(-5% Pertumbuhan ; -10 Air Penyiraman ; Air bisa menguap ; Tanaman lebih haus)");
            	break;
    		}
				puts("===================================================");
				puts("");
				printf("Ini adalah hari ke - %d. Mau ngapain hari ini?\n", hari);
				puts("");
		
				printf("|Taneman 1\t: %-14s|\n", tanamanAwal);
				printf("|Dehidrasi\t: %d%%\t\t|\n", airTanaman);
				printf("|Pertumbuhan\t: %d%%\t\t|\n", pertumbuhanTanaman); 
			}
		}
		
		if (masihBisaNgerawat == true) {
			puts("");
			printf("Hari ini mau ngapain [%s]?\n", nama);
			puts("1. Siram tanaman");
			puts("2. Mupuk tanaman");
			puts("3. Diemin ajah");
			int hariIniMauNgapain;
			scanf("%d", &hariIniMauNgapain); getchar();
			switch(hariIniMauNgapain) {
				case 1:
					system("cls");
					int *nyiramTanaman = &airTanaman;
					fungsiNyiramTanaman(nyiramTanaman, randomMusim);
					hari++;
				break;
				
				case 2:
					system("cls");
					int *mupukTanaman = &pertumbuhanTanaman;
					fungsiMupukTanaman(mupukTanaman, randomMusim);
					hari++;
				break;
			
				case 3:
					system("cls");
		
				break;
			
				default: 
					printf("Pilihan mu tidak valid [%s]. Pilih hanya pilihan 1 - 3.", nama);
					puts("Tekan 'enter' untuk lanjut.");
					printf(">> ");
					getchar();
			}
			
			// Setiap 1 hari beres, air bakal ngurang
			int *penguranganAirTanaman = &airTanaman;
			penguranganAirRandom(penguranganAirTanaman, randomMusim);
		
			// Setiap 1 hari beres, pertumbuhan bakal nambah
			int *pertambahanPertumbuhanTanaman = &pertumbuhanTanaman;
			pertambahanPertumbuhanRandom(pertambahanPertumbuhanTanaman, randomMusim);
		
			// Hitung skor berdasarkan pertumbuhan
        	if (hari == 7) { // Misalnya, jika hari terakhir
            skor = pertumbuhanTanaman; // Skor berdasarkan pertumbuhan
        }

		}
		system("cls");
	}
	// Simpan skor ke file setelah permainan berakhir
    struct Player p;
    strcpy(p.nama, nama);
    p.skor = skor;
    tambahSkorKeFile("scoreboard.txt", p); // Simpan skor ke file
}



// Menu Tutorial
void menuTutorial(){
	puts("Selamat datang di Tutorial PlanTra.");
	puts("================================");
	puts("Ini cara mainnya:");
	puts("1. Ketik [1] untuk mulai permainan pada menu utama.");
	puts("2. Mainkan gamenya kocak, lu mau ngapain lagi.");
	puts("3. Ketik [3] jika ingin keluar.");
	puts("================================");
	puts("Tekan 'enter' untuk lanjut.");
	printf(">> ");
	getchar();
	system("cls");
}



void menuExit(){
	system("cls");
	
	keluar = 0;
	
	bool validasiValidasiKeluar = true;
	
	while (validasiValidasiKeluar){
		puts("Yakin mau keluar? [Y] [N]");
	
		char validasiKeluar;
	
		scanf("%c", &validasiKeluar); getchar();
	
		if (validasiKeluar == 'Y' || validasiKeluar == 'y'){
			system("cls");
			puts("Makasih udah main. Balik lagi ya!");
			keluar = 1;
			validasiValidasiKeluar = false;
		}
		else if (validasiKeluar == 'N' || validasiKeluar == 'n') {system("cls"); validasiValidasiKeluar = false;}
		else {		
		system("cls");
		puts("\033[0;31mMaaf input anda tidak valid.");
		printf("\033[0m");
		}
	}

}



int main(){
	
	menuMulai();

	bool kondisiMenuAwal = true;

	while(kondisiMenuAwal){
		printf("Halo [%s] selamat datang di Menu Utama PlanTra!\n", nama);
		puts("================================");
		puts("Silahkan pilih:");
		puts("1. Main");
		puts("2. Tutorial");
		puts("3. Scoreboard");
		puts("4. Remove from Soreboard");
		puts("5. Exit");
		printf(">> ");

		int menuAwal;
		scanf("%d", &menuAwal); getchar();
	
		const char *filename = "scoreboard.txt"; // Deklarasi filename
        struct Player players[100]; // Array untuk menyimpan pemain
        int playerCount = muatScoreboardDariFile(filename, players); // Memuat scoreboard
		
		switch(menuAwal){
			case 1:
				system("cls");
				menuMain();
			break;
	
			case 2:
				system("cls");
				menuTutorial();
			break;
			
			case 3:
				system("cls");
                bubbleSort(players, playerCount); // Mengurutkan pemain
                tampilkanScoreboard(players, playerCount); // Menampilkan scoreboard
			break;
			case 4:
                system("cls");
                hapusPemain(filename, players, &playerCount); // Memanggil fungsi untuk menghapus pemain
                break;

            case 5:
                system("cls");
                menuExit();
                if (keluar == 1) {
                    return 0;
                }
                break;
	
			default:
				system("cls");
				puts("\033[0;31mMaaf input anda tidak valid.");
				printf("\033[0m");
			break;
		}

	}
	return 0;
}

