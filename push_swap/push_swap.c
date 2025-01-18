#include "push_swap.h"

stack *parser(int i, int ac, char **av, stack *head)
{
	int j;
	long temp;
	char **numbers;
	int *content;

	while (i < ac)
	{
		numbers = ft_split(av[i], ' ');
		j = 0;
		while (numbers[j])
		{
			temp = ft_atoy(numbers[j]);
			if (temp == 2147483648 || ft_lstcompare(head, (int)temp))
			{
				free_arr(&numbers);
				ft_clearlst(&head);
				return (write(2, "Error\n", 6), NULL);
			}
			ft_add_backlst(&head, ft_newlst((int)temp));
			j++;
		}
		free_arr(&numbers);
		i++;
	}
	return (head);
}

int ft_index_max(stack *head, int choice)
{
	int index;
	int max;
	int i;
	stack *curr;

	curr = head;
	index = 0;
	i = 0;
	max = -2147483648 + choice;
	while (curr != NULL)
	{
		if ((!choice && max <= curr->number) || (choice && max >= curr->number))
		{
			max = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	return (index);
}

int ft_target(int number, stack **head_B, int choice)
{
	stack *curr;
	int target;
	int index;
	int biggest;
	int i;
	
	i = 0;
	curr = *head_B;
	index = -1;
	target = -2147483648 + choice;
	while(curr != NULL)
	{
		if ((!choice && number > curr->number && curr->number >= target) || (choice && number < curr->number && curr->number <= target))
		{
			target = curr->number;
			index = i;
		}
		curr = curr->next;
		i++;
	}
	if (index == -1)
		index = ft_index_max(*head_B, choice);
	return (index);
}

int min(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}
int count = 0;
void moves(int choice, int operation)
{
	if (!choice && operation == 1)
		write(1, "sa\n", 3);
	if (choice && operation == 1)
		write(1, "sb\n", 3);
	if (!choice && operation == 2)
		write(1, "pb\n", 3);
	if (choice && operation == 2)
		write(1, "pa\n", 3);
	if (!choice && operation == 3)
		write(1, "ra\n", 3);
	if (choice && operation == 3)
		write(1, "rb\n", 3);
	if (!choice && operation == 4)
		write(1, "rra\n", 4);
	if (choice && operation == 4)
		write(1, "rrb\n", 4);
	count++;
}

void ft_move_cheapest(stack **head_A, stack **head_B, int *lci, int choice)
{
	int size_A;
	int size_B;

	size_A = ft_sizelst(*head_A);
	size_B = ft_sizelst(*head_B);
	while (1)
	{
		// you should handle rr and rrr, see garbage.txt
		if (lci[0] <= size_A / 2 && lci[0])
			ft_rot(head_A), lci[0]--, moves(choice, 3);
		else if (lci[0] > size_A / 2 && lci[0] != size_A)
			ft_revrot(head_A), lci[0]++, moves(choice, 4);
		if (lci[1] <= size_B / 2 && lci[1])
			ft_rot(head_B), lci[1]--, moves(choice + 1, 3);
		else if (lci[1] > size_B / 2 && lci[1] != size_B)
			ft_revrot(head_B), lci[1]++, moves(choice + 1, 4);
		if ((!lci[0] || lci[0] == size_A) && (!lci[1] || lci[1] == size_B))
			break ;
	}
	ft_push(head_A, head_B), moves(choice, 2);
}

void ft_cost(stack **head_A, stack **head_B, int choice)
{
	long temp_cost;
	long curr_cost;
	stack *curr;
	int temp;
	int i;
	int lci[2]; // least cost index
	int size_A;
	int size_B;

	curr = *head_A;
	i = 0;
	size_A = ft_sizelst(*head_A);
	size_B = ft_sizelst(*head_B);
	while (curr != NULL)
	{
		temp = ft_target(curr->number, head_B, choice);
		curr_cost = min(i, size_A - i) + min(temp, size_B - temp);
		if (curr == *head_A || curr_cost < temp_cost)
		{
			lci[0] = i;
			lci[1] = temp;
			temp_cost = curr_cost;
		}
		curr = curr->next;
		i++;
	}
	ft_move_cheapest(head_A, head_B, lci, choice);
}

int main(int ac, char **av)
{
	stack *head;
	stack *head_b;
	int min;
	int size;

	if (ac < 2)
		return (0);
	head = parser(1, ac, av, (stack *)NULL);

	// pushing 2 elements to B to start the algo
	while (ft_sizelst(head) > 3 && ft_sizelst(head_b) < 2)
		ft_push(&head, &head_b), moves(0, 2);
	
	// moving least cost element in each iteration
	while (ft_sizelst(head) > 3)
		ft_cost(&head, &head_b, 0);
	
	ft_sort3(&head);

	// moving least cost element in each iteration
	while (ft_sizelst(head_b))
		ft_cost(&head_b, &head, -1);
	
	// making sure the smallest number is at the top
	min = ft_index_max(head, -1);
	size = ft_sizelst(head);
	while (1)
	{
		if (min && min <= size / 2)
			ft_rot(&head), min--, moves(0, 3);
		else if (min != size && min > size / 2)
			ft_revrot(&head), min++, moves(0, 4);
		else break;
	}

	// printing the 2 stacks
	// ft_iterlst(head, f);
	// printf("------------------------------------\n");
	// ft_iterlst(head_b, f);

	ft_clearlst(&head);
	ft_clearlst(&head_b);
	printf("count is: %d\n", count);
}
//99 0 25 -38 10 7 42
//ARG="14 -2 13 -18 20 17 7 -7 18 19 -14 -4 -3 12 8 -9 15 -1 6 -5"; ./push_swap $ARG | ./checker_linux $ARG
//ARG="86943 93572 -61005 -1543 78344 42838 -23262 69757 56958 -14894 6134 31633 12874 -38707 -48425 -93212 36431 87115 -59096 45046 83954 65041 35470 -79624 85992 -5337 -5500 40592 22301 32235 29131 -41730 52212 -90728 24553 -30770 -23770 -43154 14888 -60492 56882 -34653 32199 -74933 -84974 90633 -6426 -79810 33940 14391 49520 64507 10841 47264 25741 -48553 96195 -96856 -87495 12278 -34650 -75948 -21840 -41184 -89373 21755 -29751 -94975 74738 27516 -93173 68306 89224 -62768 39177 -79180 61075 2164 59505 -73150 6404 34646 52805 -8871 98312 -12047 -30412 -29676 97031 42093 6408 38919 -40978 98939 92672 43018 8619 -30079 -69909 -54218 74068 -95225 -1722 -39037 60676 -68425 -69703 60507 45826 -39263 -97341 52209 -93583 -59757 -81281 -25113 -78336 -91174 15747 71454 -89916 43847 -82635 9509 -97178 -17867 31278 -67062 49384 52933 -17907 -985 40216 -9467 64815 94523 -82436 69706 89985 23490 -50226 47865 93905 -85721 -67311 -58334 -97816 -94136 60235 -59495 98122 14052 77879 1447 -65553 -25865 45744 88401 -50762 22203 60272 96081 66235 77595 -76476 -23880 -19738 -84738 94432 22427 93423 -27643 -49204 15619 -67576 -86435 77168 -85725 -10476 -34188 11220 -61697 62644 -20386 -74173 37056 -82 -26385 82942 20762 -16994 -45202 72832 21851 -19505 -34157 -58489 65027 66355 -16346 42556 12064 36114 -42499 -7070 -89412 31354 80801 71772 -93336 -58256 -78547 -49932 -26949 50525 66037 59131 9511 25332 31919 86721 -89043 16865 12804 47358 -51452 -33618 -38923 89456 -63346 -27337 23630 76914 83004 47303 9082 42249 -26463 -88356 -51829 38605 -10527 -66822 -6963 91082 97525 -60826 44655 9163 78699 64314 13507 -48702 -98938 2989 29923 -78614 -67537 37088 16982 17198 -70304 53293 -80684 97151 69317 87690 -57023 -98191 91243 13145 -22562 -31733 -83259 -86182 -66392 92132 16081 -45882 -64406 4988 -11827 31625 -8804 -65019 19792 -28665 15904 -43187 77655 -17565 -18936 -47039 -8434 -44262 -60090 15015 -73512 -26048 -5361 -25758 73561 83121 38373 -80031 82618 -44784 15642 -7067 -73276 58145 -93888 9090 -93231 -1080 96477 93339 -37067 13093 -23434 -72408 98410 81754 59807 -50575 -54438 40645 3871 26940 -14739 54688 -62809 83455 -32458 -98430 20447 95975 -89201 -28571 -33808 1363 -59010 -92302 -67727 25168 37952 -14670 17842 -58043 -26169 59404 46233 -44943 96024 94204 -57511 2492 -72976 1027 31830 37178 26836 40375 6115 -70151 48925 -7193 -96618 -42647 28539 -20417 89752 59875 17728 -47753 45380 -12953 -23088 35837 -26525 60763 -44983 7547 8059 30131 -94512 -22314 33517 28079 -9693 -14694 -59394 63643 -59230 3707 37871 -53121 14558 67509 -10292 60460 -31000 -20468 -79527 9806 66626 -3249 47299 -11417 -43504 -43657 83931 -72507 -55333 42684 -77250 43614 -42330 83450 36537 53145 -23253 -63837 -93593 -50295 55974 -332 45818 -22904 -33102 -23978 95569 40331 -52661 -60041 -18392 -70006 79533 14398 -76427 87176 75568 -86283 -71674 55134 77715 22680 -9400 -95852 39676 16049 -25146 -11008 70800 89039 73220 50937 -94551 -19889 69112 15553 -6122 68763 42152 12158 64757 45081 80238 -81499 85661 12519 -32250 39879 -33439 7184 -25733 -14146 -9867 -87523 87635 17383 88172 69685 85302 -69783 37904 58360 73315 67354 57762 16339 -82352 -5085 -72885 -26546 31283 -18607 -34333 -12316 10529"; ./push_swap $ARG | ./checker_linux $ARG
//ARG="2829 -82862 -95739 -65116 -23767 30873 98670 -95425 19137 -97125 83765 -35796 13709 15784 15607 -51409 1505 64440 -42622 -35980 -49694 64811 -38817 -38167 -43374 54305 53572 66780 -31641 -96634 54335 179 -28231 -22553 -23941 -97855 -94563 -93407 85694 -87413 39044 23481 -99444 34464 -63747 -58050 20930 -25852 -91640 -33843 -15281 4850 -74170 -84405 30621 -35190 82232 -32166 -23127 14246 -88746 -84813 -23461 40021 19147 -2679 49326 23100 -90321 74457 96666 66517 -56501 -88429 48756 43961 7732 -25535 60060 43658 -84137 -86139 -67520 -20723 -49212 32278 -85885 25255 2373 23025 -14176 98320 58281 7499 -60506 44127 76389 -18167 8121 -28822"; ./push_swap $ARG | ./checker_linux $ARG