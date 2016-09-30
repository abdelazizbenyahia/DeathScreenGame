///
/// The game world manager
///

#pragma once
#include "Manager.h"
#include "ObjectList.h"
#include "Vector.h"
#include "SceneGraph.h"
namespace df
{
const std::string WORLD_MANAGER = "df::world_manager";
class WorldManager : public Manager
{

private:
    WorldManager();                      ///< Private since a singleton.
    WorldManager(WorldManager const&);   ///< Don't allow copy.
    void operator=(WorldManager const&); ///< Don't allow assignment.
    ObjectList deletions;                ///< List of all Objects to delete.
	Box boundary; /// World boundary.
	Box view; /// Player view of game world.
	Object* p_object_following; ///object the view is following
	SceneGraph scene;			///storage for all objects
public:
    /// Get the one and only instance of the WorldManager.
    static WorldManager& getInstance();

    /// Startup game world (initialize everything to empty).
    /// Return 0.
    int startUp();

    /// Shutdown game world (delete all game world Objects).
    void shutDown();

    /// updates world
    /// Delete Objects marked for deletion
    void update();

    /// draw all the Objects in the world
    void draw();

    /// Add Object to world.
    /// Return 0 if ok, else -1.
    int insertObject(Object* p_o);

    /// Remove Object from world.
    /// Return 0 if ok, else -1.
    int removeObject(Object* p_o);

    /// Return list of all Objects in world.
    /// If inactive is true, include inactive Objects.
    ObjectList getAllObjects(bool inactive = false) const;

    /// Indicate Object is to be deleted at end of current game loop.
    /// Return 0 if ok, else -1.
    int markForDelete(Object* p_o);

    /// Return list of Objects collided with at Position `where'.
    /// Collisions only with solid Objects.
    /// Does not consider if p_o is solid or not.
    ObjectList isCollision(Object* p_o, Vector where) const;
    /// Move Object.
    /// If no collision with solid, move ok else don't move.
    /// If p_go is Spectral, move ok.
    /// Return 0 if move ok, else -1 if collision with solid.
    int moveObject(Object* p_o, Vector where);

	/// Get game world boundary.
	Box getBoundary() const;
	///set boundary
	void setBoundary(Box bound);
	/// Get player view of game world.
	Box getView() const;
	/// Set player view of game world.
	void setView(Box new_view);
	/// Set view to center screen on position view_pos.
	/// View edge will not go beyond world boundary.
	void setViewPosition(Vector view_pos);
	/// Set view to center screen on Object.
	/// Set to NULL to stop following.
	/// If p_new_view_following not legit, return -1 else return 0.
	int setViewFollowing(Object *p_new_view_following);
	///get the scene graph
	SceneGraph &getSceneGraph();

};

} // end of namespace df
