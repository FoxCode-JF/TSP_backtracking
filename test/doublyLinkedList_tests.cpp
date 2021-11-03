#include "catch2/catch.hpp"

extern "C"
{
	#include "../includes/doublyLinkedList.h"
}


SCENARIO("Create a list with first node and add another at head and delete node at head")
{
	GIVEN("List is not created")
	{
		WHEN("Head and tail are empty")
		{
			Node_t* head = NULL; 
			Node_t* tail = NULL;

			THEN("Create list by adding a node")
			{
				tail = addNodeAtHead(&head, 1);
				REQUIRE(((tail == head) && (head->data == 1)));
			
				THEN("Add another node at head")
				{
					(void)(addNodeAtHead(&head, 2));
					REQUIRE(((tail != head) && (head->data == 2)));
					
					WHEN("Nodes added at head")
					{
						int data_beforeDelete = head->data;

						THEN("Delete Node at head")
						{
							deleteNodeAtHead(&head);
							int data_afterDelete = head->data;
							REQUIRE(data_beforeDelete != data_afterDelete);
						}
					}
				}
			}
		}
	}
}

SCENARIO("Add node at tail and delete node at tail")
{
	GIVEN("List")
	{
		size_t listSize = 6;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		for (size_t i = 0; i < listSize; i++)
		{
			if ( tail == NULL)
			{
				tail = addNodeAtHead(&head, i);
			}
			else 
			{
				(void)addNodeAtHead(&head, i);
			}
		}

		WHEN("Node added at tail")
		{	
			int valueToAdd = 1111;
			addNodeAtTail(&tail, valueToAdd);
			printList(head);
			THEN("Expected data present at tail")
			{
				REQUIRE(tail->data == valueToAdd);
			}
		}	
	}
}

SCENARIO("Add node at index and delete that node")
{
	GIVEN("List and index")
	{
		size_t listSize = 6;
		uint8_t index = 3;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		for (size_t i = 0; i < listSize; i++)
		{
			if ( tail == NULL)
			{
				tail = addNodeAtHead(&head, i);
			}
			else 
			{
				(void)addNodeAtHead(&head, i);
			}
		}

		WHEN("Node added at index")
		{	
			int valueToAdd = 1111;
			printList(head);
			addNodeAtIndex(&head, valueToAdd, index);
			printList(head);

			THEN("Expected data present at index")
			{	
				Node_t* current;
				current = head;

				for (size_t i = 0; i < index; i++)
				{
					current = current->next;
				}

				printList(head);
				REQUIRE(current->data == valueToAdd);
			}

			WHEN("Data present at index")
			{
				Node_t* current;
				current = head;

				for (size_t i = 0; i < index; i++)
				{
					current = current->next;
				}

				int data_beforeDelete = current->data;

				THEN("Delete node at index")
				{
					deleteNodeAtIndex(&head, index);
					
					current = head;
					for (size_t i = 0; i < index; i++)
					{
						current = current->next;
					}
					int data_afterDelete = current->data;
					REQUIRE(data_beforeDelete != data_afterDelete);
				}
			}
		}	
	}
}

// SCENARIO("Delete entire List")
// {
// 	GIVEN("List")
// 	{
// 		size_t listSize = 6;
// 		Node_t* head = NULL; 
// 		Node_t* tail = NULL;
// 		for (size_t i = 0; i < listSize; i++)
// 		{
// 			if ( tail == NULL)
// 			{
// 				tail = addNodeAtHead(&head, i);
// 			}
// 			else 
// 			{
// 				(void)addNodeAtHead(&head, i);
// 			}
// 		}

// 		WHEN("List is created")
// 		{
// 			THEN("Delete whole list")
// 			{
// 				// deleteList(&head, &tail);
// 				REQUIRE(((head = NULL) && (tail == NULL)));
// 			}
// 		}
// 	}
// }

// #define SEC_PER_MIN			60
// #define MIN_TO_SEC(min)		((min) * SEC_PER_MIN)

// static const game_time_t DEFAULT_BASE_TIME = MIN_TO_SEC(5);

// static void init_game_with_time_config(game_time_t base_time, game_time_t bonus_per_move = 0)
// {
// 	struct time_config config;
// 	config.base_time = base_time;
// 	config.bonus_per_move = bonus_per_move;
// 	game_init(&config);
// }

// static void init_game_with_defaults()
// {
// 	init_game_with_time_config(DEFAULT_BASE_TIME);
// }
// SCENARIO("Game initialization")
// {
// 	GIVEN("Time configured to 5 minutes")
// 	{
// 		const game_time_t time_expected = MIN_TO_SEC(5);
			
// 		WHEN("Game is initialized")
// 		{
// 			init_game_with_time_config(time_expected);

// 			THEN("Player one with 5 minutes left")
// 			{
// 				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);
// 				REQUIRE(p1_time_left == time_expected);
// 			}

// 			THEN("Player two with 5 minutes left")
// 			{
// 				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);
// 				REQUIRE(p2_time_left == time_expected);
// 			}
// 		}
// 	}

// 	GIVEN("Time configured to 15 minutes")
// 	{
// 		game_time_t time_expected = MIN_TO_SEC(15);
			
// 		WHEN("Game is initialized")
// 		{
// 			init_game_with_time_config(time_expected);

// 			THEN("Player one with 15 minutes left")
// 			{
// 				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);
// 				REQUIRE(p1_time_left == time_expected);
// 			}
// 			THEN("Player two with 15 minutes left")
// 			{
// 				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);
// 				REQUIRE(p2_time_left == time_expected);
// 			}
// 		}
// 	}
// }

// SCENARIO("Game starting")
// {
// 	WHEN("Game is initialized")
// 	{
// 		init_game_with_defaults();

// 		THEN("Game is not started")
// 		{
// 			REQUIRE(false == game_is_started());
// 		}

// 		WHEN("Game started")
// 		{
// 			game_start();

// 			THEN("Game is started")
// 			{
// 				REQUIRE(true == game_is_started());
// 			}

// 			WHEN("Game is paused")
// 			{
// 				game_pause();

// 				THEN("Game is not started")
// 				{
// 					REQUIRE(false == game_is_started());
// 				}
// 				WHEN("Game started again")
// 				{
// 					game_start();

// 					THEN("Game is started")
// 					{
// 						REQUIRE(true == game_is_started());
// 					}	
// 				}
// 			}
// 		}
// 	}
// }

// SCENARIO("Switching player turn")
// {
// 	WHEN("Game is not started")
// 	{
// 		init_game_with_defaults();

// 		THEN("No player to move")
// 		{
// 			REQUIRE(PLAYER_NONE == get_current_player());
// 		}

// 		WHEN("Game started")
// 		{
// 			game_start();

// 			THEN("Player one turn")
// 			{
// 				REQUIRE(PLAYER_ONE == get_current_player());
// 			}

// 			WHEN("Player one moved")
// 			{
// 				game_current_player_moved();

// 				THEN("Player two turn")
// 				{
// 					REQUIRE(PLAYER_TWO == get_current_player());		
// 				}

// 				WHEN("Player two moved")
// 				{
// 					game_current_player_moved();
				
// 					THEN("Player one turn")
// 					{
// 						REQUIRE(PLAYER_ONE == get_current_player());		
// 					}
// 				}

// 				WHEN("Game paused")
// 				{
// 					game_pause();

// 					WHEN("Game is resumed")
// 					{
// 						game_start();

// 						THEN("Player two turn")
// 						{
// 							REQUIRE(PLAYER_TWO == get_current_player());
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }


// SCENARIO("Second elapsed")
// {
// 	GIVEN("After init - game not started")
// 	{
// 		const game_time_t time_expected = MIN_TO_SEC(5);

// 		init_game_with_time_config(time_expected);

// 		WHEN("Current player's second elapsed")
// 		{
// 			current_player_second_elapsed();

// 			THEN("Player one's time not decreased")
// 			{
// 				game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

// 				REQUIRE(DEFAULT_BASE_TIME == p1_time_left);
// 			}

// 			THEN("Player two's time not decreased")
// 			{
// 				game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

// 				REQUIRE(DEFAULT_BASE_TIME == p2_time_left);		
// 			}
// 		}

// 		WHEN("Game started")
// 		{
// 			game_start();

// 			WHEN("Current player's second elapsed")
// 			{
				
// 				current_player_second_elapsed();

// 				THEN("Player one's time decreased")
// 				{
// 					const game_time_t time_expected = DEFAULT_BASE_TIME - 1;
// 					game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

// 					REQUIRE(time_expected == p1_time_left);	
// 				}


// 				THEN("Player two's time not decreased")
// 				{
// 					game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

// 					REQUIRE(DEFAULT_BASE_TIME == p2_time_left);		
// 				}
// 			}

// 			WHEN("Game paused")
// 			{
// 				game_pause();
// 				WHEN("Current player's second elapsed")
// 				{
// 					current_player_second_elapsed();
					
// 					THEN("Player one's time not decreased")
// 					{
// 						game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

// 						REQUIRE(DEFAULT_BASE_TIME == p1_time_left);
// 					}
// 				}
// 			}
// 			WHEN("Player moved")
// 			{
// 				game_current_player_moved();

// 				WHEN("Current player's second elapsed")
// 				{
// 					current_player_second_elapsed();

// 					THEN("Player one's time not decreased")
// 					{
// 						const game_time_t time_expected = DEFAULT_BASE_TIME;
// 						game_time_t p1_time_left = player_get_time_left(PLAYER_ONE);

// 						REQUIRE(DEFAULT_BASE_TIME == p1_time_left);	
// 					}


// 					THEN("Player two's time decreased")
// 					{
// 						const game_time_t time_expected = DEFAULT_BASE_TIME - 1;
// 						game_time_t p2_time_left = player_get_time_left(PLAYER_TWO);

// 						REQUIRE(time_expected == p2_time_left);		
// 					}
// 				}
// 			}
// 		}
// 	}
// }

// SCENARIO("Time ended")
// {
// 	GIVEN("Both players have one second left")
// 	{
// 		init_game_with_time_config(1);

// 		WHEN("Game started")
// 		{
// 			game_start();

// 			THEN("Time did not end for any player")
// 			{
// 				REQUIRE(PLAYER_NONE == game_get_player_who_exceeded_time_first());
// 			}

// 			WHEN("A second elapsed for Player one")
// 			{
// 				current_player_second_elapsed();

// 				THEN("Time ended for player one")
// 				{
// 					REQUIRE(PLAYER_ONE == game_get_player_who_exceeded_time_first());
// 				}

// 				WHEN("Player one moved")
// 				{
// 					game_current_player_moved();

// 					THEN("Time ended for player one")
// 					{
// 						REQUIRE(PLAYER_ONE == game_get_player_who_exceeded_time_first());
// 					}

// 					WHEN("A second elapsed for player two")
// 					{
// 						current_player_second_elapsed();

// 						THEN("Time ended for player one")
// 						{
// 							REQUIRE(PLAYER_ONE == game_get_player_who_exceeded_time_first());
// 						}
// 					}
// 				}
// 			}

// 			WHEN("A second elapsed for Player two")
// 			{
// 				game_current_player_moved();
// 				current_player_second_elapsed();

// 				THEN("Time ended for player two")
// 				{
// 					REQUIRE(PLAYER_TWO == game_get_player_who_exceeded_time_first());
// 				}

// 				WHEN("Player two moved")
// 				{
// 					game_current_player_moved();

// 					THEN("Time ended for player two")
// 					{
// 						REQUIRE(PLAYER_TWO == game_get_player_who_exceeded_time_first());
// 					}

// 					WHEN("A second elapsed for player one")
// 					{
// 						current_player_second_elapsed();

// 						THEN("Time ended for player two")
// 						{
// 							REQUIRE(PLAYER_TWO == game_get_player_who_exceeded_time_first());
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }


// SCENARIO("Bonus time per move")
// {
// 	GIVEN("Player has 5min left and bonus time is 30s")
// 	{
// 		init_game_with_time_config(DEFAULT_BASE_TIME, 30);
// 		game_start();

// 		WHEN("Player one moved")
// 		{
// 			game_current_player_moved();

// 			THEN("Player one has 5 min and 30s left")
// 			{
// 				game_time_t time_left = player_get_time_left(PLAYER_ONE);
// 				REQUIRE(time_left == DEFAULT_BASE_TIME + 30);
// 			}
// 		}
// 	}	
// 	// Given 5 min left until the game end and bonus time is 30s, when player moves, player has 5 minutes and 30 seconds left
// 	// handle time exceeded
// }