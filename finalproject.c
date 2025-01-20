#include<stdio.h>
#include<string.h>
#define TRANSACTION_ID 10
#define BUYER_ID 10
#define SELLER_ID 10
#define SUCCESS 1
#define FAILURE 0
#define DB_SIZE 100
typedef struct BuyerEnergy{
    char buyerId[BUYER_ID];
    float totalEnergy;
}BuyerEnergy;
typedef struct PairCount {
    char buyerId[BUYER_ID];
    char sellerId[SELLER_ID];
    float revenue;
    int count;
} PairCount;
typedef struct seller_transactions{
    char seller_id[10];
    float revenue;
}st;
typedef struct Timestamp{
    int date;
    int month;
    int year;
    int hour;
    int minute;
}TS;
typedef struct Transactions{
    char TrId[TRANSACTION_ID];
    char BuyerId[BUYER_ID];
    char SellerId[SELLER_ID];
    float energy;
    float price;
    TS datetime;
    
}tr;
typedef struct TimePeriod{
    TS start;
    TS end;
} TimePeriod;

void initialise_db(tr records[]){
    for(int i=0;i<DB_SIZE;i++){
        records[i].TrId[0]='\0';
        records[i].BuyerId[0]='\0';
        records[i].SellerId[0]='\0';
        records[i].energy=0;
        records[i].price=0;
        records[i].datetime.date=0;
        records[i].datetime.month=0;
        records[i].datetime.year=0;
        records[i].datetime.hour=0;
        records[i].datetime.minute=0;
    }
}

void ListTransactionsInPeriod(tr records[], int size, TimePeriod period) {
    int found = 0; 

    for (int i = 0; i < size; i++) 
    {
        if (records[i].TrId[0] != '\0') 
        {
            if (((records[i].datetime.year > period.start.year ||
                (records[i].datetime.year == period.start.year &&
                 (records[i].datetime.month > period.start.month ||
                  (records[i].datetime.month == period.start.month &&
                   records[i].datetime.date >= period.start.date))))) && (records[i].datetime.year < period.end.year ||
                (records[i].datetime.year == period.end.year &&
                 (records[i].datetime.month < period.end.month ||
                  (records[i].datetime.month == period.end.month &&
                   records[i].datetime.date <= period.end.date)))))
                
            {
        
                printf("\nTransaction ID   : %s\n", records[i].TrId);
                printf("Buyer ID         : %s\n", records[i].BuyerId);
                printf("Seller ID        : %s\n", records[i].SellerId);
                printf("Amount of Energy  : %f\n", records[i].energy);
                printf("Selling Price     : %f\n", records[i].price);
                printf("Timestamp         : %d/%d/%d %d:%d\n",
                       records[i].datetime.date,
                       records[i].datetime.month,
                       records[i].datetime.year,
                       records[i].datetime.hour,
                       records[i].datetime.minute);
                found = 1; 
            }
        }             
    }

    if (!found) {
        printf("\n>>> No transactions found in the specified time period <<<\n");
    }
}

int Insert_Update(tr records[],int size,char tr_id[],char buy_id[],char sell_id[],float energy,float price,int date,int month, int year,int hour,int minute)
{
    int status_code=SUCCESS;
    int i,j,found,is_free_loc;
    i=0,found=0;
    while((i<size)&&!found)
    {
        if(strcmp(records[i].TrId,tr_id)==0)
        {
            found=1;
        }
        else
         i++;
    
        if(found)
        {
            strcpy(records[i].BuyerId,buy_id);
            strcpy(records[i].SellerId,sell_id);
            records[i].energy=energy;
            records[i].price=price;
            records[i].datetime.date=date;
            records[i].datetime.month=month;
            records[i].datetime.month=year;
            records[i].datetime.month=hour;
            records[i].datetime.month=minute;
        }
        else
        {
            j=0;
            is_free_loc=0;
            while((j<size)&&(is_free_loc==0))
            {
                if(records[j].TrId[0]=='\0')
                is_free_loc=1;
                else
                j++;
            }
            if(is_free_loc==1)
            {
                strcpy(records[j].TrId,tr_id);
                strcpy(records[j].BuyerId,buy_id);
                strcpy(records[j].SellerId,sell_id);
                records[j].energy=energy;
                records[j].price=price;
                records[j].datetime.date=date;
                records[j].datetime.month=month;
                records[j].datetime.month=year;
                records[j].datetime.month=hour;
                records[j].datetime.month=minute;
                found=1;
            }
            else
            status_code= FAILURE;
        }
    }
    return status_code;

}
void View_Transactions(tr records[], int size)
{
    int i=0;
    while(records[i].TrId[0]!='\0')
    {
         printf("\n");
         printf("Transaction id   : %s\n",records[i].TrId);
         printf("Buyer Id         : %s\n",records[i].BuyerId); 
         printf("Seller Id        : %s\n",records[i].SellerId);
         printf("Amount of Energy : %f\n",records[i].energy);
         printf("Selling price    : %f\n",records[i].price);
         printf("Timestamp        : %d/%d/%d %d:%d\n",records[i].datetime.date,records[i].datetime.month,records[i].datetime.year,records[i].datetime.hour,records[i].datetime.minute);
         i++;
    }
}
float total_seller_revenue(tr records[],int size,char seller_id[])
{
    int i=0;
    float revenue=0;
    while(i<size)
    {
        if(strcmp(records[i].SellerId,seller_id)==0)
        {
            revenue+=records[i].energy*records[i].price;
            i++;
        }
        else
        i++;
    }
    return revenue;
}
void Buyer_Transaction(tr records[], int size, char transID[])
{
    int status;
    int i=0;
    while((i<size)&&(records[i].BuyerId[0]!='\0'))
    {
        if(strcmp(records[i].BuyerId,transID)==0)
        {
          status = SUCCESS;
          
            printf("Seller Id       : %s\n",records[i].SellerId);
            printf("Transaction Id  : %s\n",records[i].TrId);
            printf("Energy amt      : %f\n",records[i].energy);
            printf("Cost of Energy  : %f\n",records[i].price);
            printf("timestamp       : %d/%d/%d %d:%d\n",records[i].datetime.date,records[i].datetime.month,records[i].datetime.year,records[i].datetime.hour,records[i].datetime.minute);
            printf("\n");
        }
         i++;
    }
    if(status!=SUCCESS)
    {
        printf("\n>>> No such Buyer found <<<\n");
    }
   
    
}
void Seller_Transaction(tr records[], int size, char sellerID[])
{
    int status;
    int i=0;
    while((i<size )&&(records[i].SellerId[0]!='\0'))
    {
        if(strcmp(records[i].SellerId,sellerID)==0)
        {
          status = SUCCESS;
  
            printf("Buyer Id        : %s\n",records[i].BuyerId);
            printf("Transaction Id  : %s\n",records[i].TrId);
            printf("Energy amt      : %f\n",records[i].energy);
            printf("timestamp       : %d/%d/%d %d:%d\n",records[i].datetime.date,records[i].datetime.month,records[i].datetime.year,records[i].datetime.hour,records[i].datetime.minute);
            printf("\n");
        }
        if(status!=SUCCESS)
        {
            printf("\n>>> No such Seller found <<<\n");
        }
        i++;
    }
}
int Check_Transaction(tr records[], int size, char transId[])
{
    int status;
    int i=0;
    int found=0;
    while(i<size && found==0)
    {
        if(strcmp(records[i].TrId,transId)==0)
        {
          status = SUCCESS;
          found=1;
            printf("Buyer Id        : %s\n",records[i].BuyerId);
            printf("Seller Id       : %s\n",records[i].SellerId);
            printf("Energy amt      : %f\n",records[i].energy);
            printf("timestamp       : %d/%d/%d %d:%d",records[i].datetime.date,records[i].datetime.month,records[i].datetime.year,records[i].datetime.hour,records[i].datetime.minute);
            
        }
        i++;
    }
    if(status!=SUCCESS)
    {
        printf("\n>>> No such Transaction found <<<\n");
    }
    
}
int FindMaxTransactionMonth(tr records[],int size)
{
    int arr[12]={0};
    int i=0;
    while(records[i].TrId[0]!='\0'&&(i<size))
    {
        arr[records[i].datetime.month-1]++;
        i++;
    }
    int max=arr[0];
    for(int j=0;j<12;j++)
    {
        if(max<arr[j])
        max=arr[j];
    }
    for(int j=0;j<12;j++)
    {
        if(max==arr[j])
        {
           switch(j)
           {
            case 1:
                printf("Maximum transactions occured in January");
                break;
            case 2:
                printf("Maximum transactions occured in February\n");
                break;
            case 3:
                printf("Maximum transactions occured in March\n");
                break;
            case 4:
                printf("Maximum transactions occured in April\n");
                break;
            case 5:
                printf("Maximum transactions occured in May\n");
                break;
            case 6:
                printf("Maximum transactions occured in July\n");
                break;
            case 7:
                printf("Maximum transactions occured in August\n");
                break;
            case 8:
                printf("Maximum transactions occured in September\n");
                break;
            case 9:
                printf("Maximum transactions occured in october\n");
                break;
            case 10:
                printf("Maximum transactions occured in November\n");
                break;
            case 11:
                printf("Maximum transactions occured in December\n");
                break;
           }
                    

        }
    }
}
void list_of_sellers(tr records[],int size)
{
    int j=0,unique_sellers=0,i;
    st revenue_arr[100];
    int found=0,sort;
    for(int i=0;i<100;i++)
    {
        revenue_arr[i].seller_id[0]='\0';
        revenue_arr[i].revenue=0;
    }
    while(j<size)
    {
        i=0;
        while((revenue_arr[i].seller_id[0]!='\0')&&(!found))
        {
            if(strcmp(revenue_arr[i].seller_id,records[j].SellerId)==0)
            found=1;
            else
            i++;
        }
        if(!found)
        {
            i=0;
            while(revenue_arr[i].seller_id[0]!='\0')
            {
                i++;
            }
            strcpy(revenue_arr[i].seller_id,records[j].SellerId);
            revenue_arr[i].revenue=total_seller_revenue(records,DB_SIZE,records[j].SellerId);
            unique_sellers+=1;
        }
        j++;
        found=0;
    }
    st temp;
    for(i=0;(i<unique_sellers-1)&&(sort==0);i++)
        {
            sort=1;
            for(j=0;j<unique_sellers-i-1;j++)
                {
                    if(revenue_arr[j].revenue>revenue_arr[j+1].revenue)
                    {
                        temp=revenue_arr[j];
                        revenue_arr[j]=revenue_arr[j+1];
                        revenue_arr[j+1]=temp;
                        sort=0;
                    }
                        
                }
        }
    for(int k=0;(k<unique_sellers)&&(revenue_arr[k].seller_id[0]!='\0');k++)
        {
            printf("Seller ID: %s\n",revenue_arr[k].seller_id);
            printf("revenue generated: %f\n",revenue_arr[k].revenue);
        }
    
}
void findMaxTransactionPair(tr records[], int size, int k) {
    PairCount pairs[DB_SIZE] = {0};
    int pairCount = 0;

    for (int i = 0; i < size && records[i].TrId[0] != '\0'; i++) {
        int found = 0;
	pairs[i].revenue=0;
        // Check if this buyer-seller pair is already in the pairs array
        for (int j = 0; (j < pairCount)&&(!found); j++) {
            if (strcmp(pairs[j].buyerId, records[i].BuyerId) == 0 &&
                strcmp(pairs[j].sellerId, records[i].SellerId) == 0) {
                pairs[j].count++;
                pairs[i].revenue+=(records[i].price*records[i].energy);
                found = 1;
                
            }
        }

        // If not found, add a new entry for this pair
        if (!found) {
            strcpy(pairs[pairCount].buyerId, records[i].BuyerId);
            strcpy(pairs[pairCount].sellerId, records[i].SellerId);
            pairs[i].revenue += (records[i].price*records[i].energy);
            pairs[pairCount].count = 1;
            pairCount++;
        }
    }

    // Find the pair with the maximum transaction count
    int maxCount = 0;
    int maxIndex = -1;
    for (int i = 0; i < pairCount; i++) {
        if (pairs[i].count > maxCount) {
            maxCount = pairs[i].count;
            maxIndex = i;
        }
    }

    // Output the pair with the maximum transactions
    if(k==0){
    	if (maxIndex != -1) {
        	printf("\n>>> Buyer-Seller pair with maximum transactions: <<<\n");
        	printf("Buyer ID: %s\n", pairs[maxIndex].buyerId);
        	printf("Seller ID: %s\n", pairs[maxIndex].sellerId);
        	printf("Number of transactions: %d\n", pairs[maxIndex].count);
        
    	} else {
        printf("\n>>> No transactions found <<<\n");
    	}
    }
	int sort;
   //sorting with respect to max  number of transaction pairs
   if(k==1){
    	for (int i = 0; (i < pairCount - 1)&&(sort!=1); i++) {
		sort =1;
        	for (int j = 0; j < pairCount - i - 1; j++) {
            		if (pairs[j].count < pairs[j + 1].count) { 
               		 PairCount temp = pairs[j];
               			 pairs[j] = pairs[j + 1];
               			 pairs[j + 1] = temp;
               			 sort=0;
           	 }
       		}
	 }
	for(int i=0;i<pairCount;i++)
	{
		printf("%s\n",pairs[i].sellerId);
		printf("%s\n",pairs[i].buyerId);
		printf("%d\n",pairs[i].count);
		printf("\n");
	}
   }
   //sorting with respect to revenue exchange between a pair
   if(k==2){	
   	for (int i = 0; (i < pairCount - 1)&&(sort!=1); i++) {
		sort =1;
        	for (int j = 0; j < pairCount - i - 1; j++) {
            	if (pairs[j].revenue < pairs[j + 1].revenue) { 
                	PairCount temp = pairs[j];
                	pairs[j] = pairs[j + 1];
                	pairs[j + 1] = temp;
                	sort=0;
            		}
        	}
	}
	for(int i=0;i<pairCount;i++)
	{
		printf("%s\n",pairs[i].sellerId);
		printf("%s\n",pairs[i].buyerId);
		printf("%f\n",pairs[i].revenue);
		printf("\n");
	}
    }
}


void FindAndDisplayMaxEnergyTransaction(tr records[], int size) {
    float maxEnergy = 0;
    int maxIndex = -1;

    // Find the transaction with the highest energy
    for (int i = 0; i < size; i++) {
        if (records[i].TrId[0] != '\0' && records[i].energy > maxEnergy) {
            maxEnergy = records[i].energy;
            maxIndex = i;
        }
    }
        // Display the transaction details if found
    if (maxIndex != -1) {
        printf("\n>>> Transaction with the Highest Energy Amount: <<<\n");
        printf("Transaction ID   : %s\n", records[maxIndex].TrId);
        printf("Buyer ID         : %s\n", records[maxIndex].BuyerId);
        printf("Seller ID        : %s\n", records[maxIndex].SellerId);
        printf("Amount of Energy  : %f kWh\n", records[maxIndex].energy);
        printf("Selling Price     : %f\n", records[maxIndex].price);
        printf("Timestamp         : %d/%d/%d %d:%d\n",
               records[maxIndex].datetime.date,
               records[maxIndex].datetime.month,
               records[maxIndex].datetime.year,
               records[maxIndex].datetime.hour,
               records[maxIndex].datetime.minute);
    } else {
        printf("\n>>> No transactions found <<<\n");
    }

}
void SortTransactionsByEnergy(tr records[], int size) {
    int sort;
    for (int i = 0; (i < size - 1)&&(sort!=1); i++) {
    	sort=1;
        for (int j = 0; j < size - i - 1; j++) {
            if (records[j].energy < records[j + 1].energy) { // Sort in decreasing order
                tr temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                sort=0;
            }
        }
    }
}
void CalculateTotalEnergyBought(tr records[], int size, BuyerEnergy buyerEnergies[], int *buyerCount) {
    *buyerCount = 0;

    for (int i = 0; i < size; i++) {
        if (records[i].TrId[0] != '\0') {
            int found = 0;

            // Check if the buyer already exists in the array
            for (int j = 0; j < *buyerCount; j++) {
                if (strcmp(buyerEnergies[j].buyerId, records[i].BuyerId) == 0) {
                    buyerEnergies[j].totalEnergy += records[i].energy;
                    found = 1;
                    break;
                }
            }

            // If not found, add a new entry for this buyer
            if (!found) {
                strcpy(buyerEnergies[*buyerCount].buyerId, records[i].BuyerId);
                buyerEnergies[*buyerCount].totalEnergy = records[i].energy;
                (*buyerCount)++;
            }
        }
    }
}
void SortBuyersByEnergy(BuyerEnergy buyerEnergies[], int buyerCount) {
    int sort;
    for (int i = 0; (i < buyerCount - 1)&&(sort!=1); i++) {
    	sort=1;
        for (int j = 0; j < buyerCount - i - 1; j++) {
            if (buyerEnergies[j].totalEnergy < buyerEnergies[j + 1].totalEnergy) { // Sort in decreasing order
                BuyerEnergy temp = buyerEnergies[j];
                buyerEnergies[j] = buyerEnergies[j + 1];
                buyerEnergies[j + 1] = temp;
                sort=0;
            }
        }
    }
}



int main()
{
    int i,n,date,month,year,hour,minute,entry_count;
    n=1;
    int buyerCount;
    float energy,price;
    char transaction_id[TRANSACTION_ID];
    char buyer_id[BUYER_ID];
    char seller_id[SELLER_ID];
    TimePeriod period;
    tr grid_db[DB_SIZE];
    initialise_db(grid_db);
    const char *sampleData[30][3] = {
        {"gxhy0012", "buy001", "sl001"},
        {"gxhy1013", "buy001", "sl001"},
        {"gxhy2123", "buy002", "sl001"},
        {"ghxy3033", "buy001", "sl002"},
        {"ghxy4314", "buy001", "sl001"},
        {"ghxy5055", "buy003", "sl003"},
        {"ghxy0666", "buy001", "sl001"},
        {"ghxy1277", "buy002", "sl002"},
        {"ghxy8198", "buy002", "sl001"},
        {"ghxy9099", "buy001", "sl003"},
        {"ghxy1000", "buy001", "sl001"},
        {"ghxy1100", "buy002", "sl002"},
        {"ghxy1200", "buy003", "sl001"},
        {"ghxy1300", "buy001", "sl002"},
        {"ghxy1400", "buy001", "sl001"},
        {"ghxy1500", "buy002", "sl001"},
        {"ghxy1610", "buy002", "sl002"},
        {"ghxy1220", "buy001", "sl003"},
        {"ghxy1800", "buy003", "sl002"},
        {"ghxy1919", "buy002", "sl001"},
        {"ghxy2000", "buy001", "sl001"},
        {"ghxy2100", "buy002", "sl002"},
        {"ghxy2200", "buy003", "sl001"},
        {"ghxy2234", "buy001", "sl003"},
        {"ghxy2400", "buy002", "sl002"},
        {"ghxy2123", "buy001", "sl001"},
        {"ghxy1234", "buy003", "sl003"},
        {"ghxy6879", "buy002", "sl001"},
        {"ghxy2124", "buy001", "sl002"},
        {"ghxy2901", "buy003", "sl001"}
    };

    // Hardcoded timestamps as integers
    int timestamps[30][5] = {
        {1, 10, 2024, 10, 15}, // 2024-10-01 10:15
        {1, 10, 2024, 11, 30}, // 2024-10-01 11:30
        {2, 10, 2024, 12, 45}, // 2024-10-02 12:45
        {2, 10, 2024, 13, 0},  // 2024-10-02 13:00
        {2, 10, 2024, 14, 5},  // 2024-10-02 14:05
        {3, 10, 2024, 15, 15}, // 2024-10-03 15:15
        {3, 10, 2024, 16, 20}, // 2024-10-03 16:20
        {3, 10, 2024, 17, 10}, // 2024-10-03 17:10
        {4, 10, 2024, 18, 30}, // 2024-10-04 18:30
        {4, 10, 2024, 19, 25}, // 2024-10-04 19:25
        {5, 10, 2024, 20, 0},  // 2024-10-05 20:00
        {5, 10, 2024, 21, 15}, // 2024-10-05 21:15
        {5, 10, 2024, 22, 30}, // 2024-10-05 22:30
        {6, 10, 2024, 23, 10}, // 2024-10-06 23:10
        {7, 10, 2024, 0, 45},  // 2024-10-07 00:45
        {7, 10, 2024, 1, 30},  // 2024-10-07 01:30
        {7, 10, 2024, 2, 0},   // 2024-10-07 02:00
        {8, 10, 2024, 3, 0},   // 2024-10-08 03:00
        {8, 10, 2024, 4, 10},  // 2024-10-08 04:10
        {9, 10, 2024, 5, 20},  // 2024-10-09 05:20
        {9, 10, 2024, 6, 30},  // 2024-10-09 06:30
        {10, 10, 2024, 7, 40}, // 2024-10-10 07:40
        {10, 10, 2024, 8, 50}, // 2024-10-10 08:50
        {11, 10, 2024, 9, 0},  // 2024-10-11 09:00
        {11, 10, 2024, 10, 10},// 2024-10-11 10:10
        {12, 10, 2024, 11, 20},// 2024-10-12 11:20
        {12, 10, 2024, 12, 30},// 2024-10-12 12:30
        {13, 10, 2024, 13, 40},// 2024-10-13 13:40
        {13, 10, 2024, 14, 50},// 2024-10-13 14:50
        {14, 10, 2024, 15, 0}  // 2024-10-14 15:00
    };

    float prices[30] = {
        100.50, 150.00, 200.75, 120.00, 130.00,
        350.50, 450.00, 600.00, 700.30, 800.50,
        900.00, 1000.00, 1100.00, 1200.00, 1300.00,
        1400.00, 1500.00, 1600.00, 1700.00, 1800.00,
        1900.00, 2000.00, 2100.00, 2200.00, 2300.00,
        2400.00, 2500.00, 2600.00, 2700.00, 2800.00
    };

    float energies[30] = {
        5.0, 6.0, 10.0, 7.5, 8.0,
        25.0, 30.0, 40.0, 45.0, 50.0,
        60.0, 70.0, 75.0, 80.0, 90.0,
        95.0, 100.0, 105.0, 110.0, 115.0,
        120.0, 125.0, 130.0, 135.0};

         for (int i = 0; i < 30; i++) {
        strcpy(grid_db[i].TrId, sampleData[i][0]);
        strcpy(grid_db[i].BuyerId, sampleData[i][1]);
        strcpy(grid_db[i].SellerId, sampleData[i][2]);
        
        grid_db[i].energy = energies[i];
        grid_db[i].price = prices[i];
        
        grid_db[i].datetime.date = timestamps[i][0];
        grid_db[i].datetime.month = timestamps[i][1];
        grid_db[i].datetime.year = timestamps[i][2];
        grid_db[i].datetime.hour = timestamps[i][3];
        grid_db[i].datetime.minute = timestamps[i][4];
    }
    
    BuyerEnergy buyerEnergies[DB_SIZE];
    while(n!=0){
    printf("\n\n\n");
    printf("Enter the number in front of the the operation that you want to perform");
     printf("\nSelect an operation:\n");
        printf("1. Insert/Update Transaction\n");
        printf("2. View Transactions\n");
        printf("3. View Seller Revenue\n");
        printf("4. View Buyer Transactions\n");
        printf("5. View Seller Transactions\n");
        printf("6. Check Transaction\n");
        printf("7. Find Max Transaction Month\n");
        printf("8. List Sellers\n");
        printf("9. Find Max Energy Transactions\n");
        printf("10. Sort Transactions by Energy\n");
        printf("11. sort the listof buyers based on the energy bought\n");
        printf("12. Find transactions in a time period\n");
        printf("13. Find Max Transaction Pair\n");
        printf("14. Sort seller-buyer pairs in decreasing order of revenue exchnged between them\n");
        printf("15. Sort the pairs in decreasing order of number of transactions between them\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                printf("how many entries do you want to perform?");
                scanf("%d",&entry_count);
                for(i=0;i<entry_count;i++){
                    printf("enter the transaction id:");
                    scanf("%s",transaction_id);
                    printf("enter the seller id:");
                    scanf("%s",seller_id);
                    printf("enter the buyer id:");
                    scanf("%s",buyer_id);
                    printf("enter the price per kWh:");
                    scanf("%f",&price);
                    printf("enter the amount of energy bought in kWh:");
                    scanf("%f",&energy);
                    printf("enter the date of transaction in DD//MM//YYYY");
                    scanf("%d %d %d",&date,&month,&year);
                    printf("enter the time of the transaction in 24 hrs format:");
                    scanf("%d %d",&hour,&minute);   
                    Insert_Update(grid_db, DB_SIZE, transaction_id, buyer_id, seller_id, energy, price, date, month, year, hour, minute);
                }
                break;

             case 2:
                View_Transactions(grid_db, DB_SIZE);
                break;

            case 3:
                printf("Enter Seller ID: ");
                scanf("%s", seller_id);
                float revenue = total_seller_revenue(grid_db, DB_SIZE, seller_id);
                printf("Total Revenue for Seller %s: %.2f\n", seller_id, revenue);
                printf("\n");
                break;

            case 4:
                printf("Enter Buyer ID: ");
                scanf("%s", buyer_id);
                Buyer_Transaction(grid_db, DB_SIZE, buyer_id);
                break;

            case 5:
                printf("Enter Seller ID: ");
                scanf("%s", seller_id);
                Seller_Transaction(grid_db, DB_SIZE, seller_id);
                break;

            case 6:
                printf("Enter Transaction ID: ");
                scanf("%s", transaction_id);
                Check_Transaction(grid_db, DB_SIZE, transaction_id);
                break;

            case 7:
                FindMaxTransactionMonth(grid_db, DB_SIZE);
                break;

            case 8:
                list_of_sellers(grid_db, DB_SIZE);
                break;

            case 9:
                FindAndDisplayMaxEnergyTransaction(grid_db, DB_SIZE);
                break;

            case 10:
                SortTransactionsByEnergy(grid_db, DB_SIZE);
                printf("Transactions sorted by energy in decreasing order.\n");
                View_Transactions(grid_db,DB_SIZE);
                break;

            case 11: 
                CalculateTotalEnergyBought(grid_db, DB_SIZE, buyerEnergies, &buyerCount);
                SortBuyersByEnergy(buyerEnergies, buyerCount);
                printf("Total energy bought by each buyer calculated and sorted.\n");
                for (int i = 0; i < buyerCount; i++) {
                    printf("Buyer ID: %s, Total Energy: %.2f kWh\n", buyerEnergies[i].buyerId, buyerEnergies[i].totalEnergy);
                }
                break;
                
            case 12:
            	printf("enter the starting date:");
            	scanf("%d %d %d",&period.start.date,&period.start.month,&period.start.year);
            	printf("enter starting time:");
            	scanf("%d %d",&period.start.hour,&period.start.minute);
            	printf("enter the starting date:");
            	scanf("%d %d %d",&period.end.date,&period.end.month,&period.end.year);
            	printf("enter starting time:");
            	scanf("%d %d",&period.end.hour,&period.end.minute);
                ListTransactionsInPeriod(grid_db,DB_SIZE,period);
                break;
                
                case 13:
                findMaxTransactionPair(grid_db, DB_SIZE,0);
                break;
                
                case 14:
                findMaxTransactionPair(grid_db, DB_SIZE,2);
                break;

		case 15:
                findMaxTransactionPair(grid_db, DB_SIZE,1);
                break;
            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
        }
    
    
    return 0;
    
}
