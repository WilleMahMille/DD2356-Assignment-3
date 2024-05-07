.PHONY : e1-run e1-send

e1-send:
	scp e1.c wija@dardel.pdc.kth.se:~/Private/a3/e1.c
bat-send:
	scp batch.sh wija@dardel.pdc.kth.se:~/Private/a3/batch.sh
e1-run:
	scp e1.c wija@dardel.pdc.kth.se:~/Private/a3/e1.c && \
	ssh wija@dardel.pdc.kth.se 'cd ~/Private/a3 && rm slurm* && cc -o e1.out e1.c && sbatch batch.sh'
