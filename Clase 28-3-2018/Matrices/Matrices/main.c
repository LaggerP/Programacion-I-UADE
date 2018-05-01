//matrices


#define FIL 4
#define COL 4
 
int main() {
	int matriz[FIL][COL] = { {1,2,3},{3,2,1},{1,3,3}};
	int f, c;

	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("%3d", matriz[f][c]);
		}
		printf("\n");
	}

}