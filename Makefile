.PHONY : e1-run e1-send

e1-send:
	scp e1.c wija@dardel.pdc.kth.se:~/Private/a3/e1.c
e1-batch:
	scp e1.sh wija@dardel.pdc.kth.se:~/Private/a3/e1.sh
e1-run:
	scp e1.c wija@dardel.pdc.kth.se:~/Private/a3/e1.c && \
	ssh wija@dardel.pdc.kth.se 'cd ~/Private/a3 && rm slurm* && cc -o e1.out e1.c && sbatch e1.sh'

e2-send:
	scp e2.c
e2-batch:
	scp e2.sh wija@dardel.pdc.kth.se:~/Private/a3/e2.sh
e2-run:
	scp e2.c wija@dardel.pdc.kth.se:~/Private/a3/e2.c && \
	scp e2.sh wija@dardel.pdc.kth.se:~/Private/a3/e2.sh && \
	ssh wija@dardel.pdc.kth.se 'cd ~/Private/a3 && rm slurm* -f && cc -o e2.out e2.c && sbatch e2.sh'

e3-send:
	scp e3.c wija@dardel.pdc.kth.se:~/Private/a3/e3.c
e3-batch:
	scp e3.sh wija@dardel.pdc.kth.se:~/Private/a3/e3.sh
e3-run:
	scp e3.c wija@dardel.pdc.kth.se:~/Private/a3/e3.c && \
	scp e3.sh wija@dardel.pdc.kth.se:~/Private/a3/e3.sh && \
	ssh wija@dardel.pdc.kth.se 'cd ~/Private/a3 && rm slurm* -f && cc -o e3.out e3.c && sbatch e3.sh'
