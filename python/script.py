import os
import shutil

num_files = [1, 2, 4, 8, 16, 32, 64, 128, 256]
# test_dir = "../testDir/testDir/"

# os.mkdir(test_dir)

for i in num_files:
    test_dir = "../tempDir/testDir{}/".format(i)
    # print(test_dir)
    if not os.path.exists(test_dir):
        os.mkdir(test_dir)
    else:
        print("Duplicating Files", test_dir)
        for j in range(i):
            shutil.copy("../temp.csv",
                        "../tempDir/testDir{}/temp{}.csv".format(i, j))

# for i in num_files:
# for i in range(1):
    # shutil.copy("../movie_metadata.csv","../testDir/testDir/{}".format("movie_metadata.csv"))
#     # print(i)
# for i in range(2):
#     shutil.copy("../movie_metadata.csv","../testDir/testDir2/{}".format("movie_metadata.csv"))
